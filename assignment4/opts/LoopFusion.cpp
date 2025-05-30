//-----------------------------------------------------------------------------
// Loop Fusion implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"
#include <llvm/ADT/SetVector.h>
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Constants.h"     // per dyn_cast<SCEVConstant>
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/APInt.h"        // per APInt
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

int loop_counter; // Serve solo per l'output

// Prototipi delle funzioni di utilità (sotto ogni corrispettivo punto)
BasicBlock* getExitGuardSuccessor(Loop &L);                                                          // Punto 1 
bool areGuardsEqual(BranchInst *G1, BranchInst *G2);                                                 // Punto 3
bool haveNotNegativeMemoryDependencies(Loop &L1, Loop &L2, ScalarEvolution &SE, DependenceInfo &DI); // Punto 4
bool haveNotNegativeScalarDependencies(Loop &L1, Loop &L2);                                          // Punto 4
bool isLoopFusionValid(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT, ScalarEvolution &SE, DependenceInfo &DI);



/**  ----- Punto 1 ----- 
* ! "Lj and Lk must be adjacent"
*
* "There cannot be any statements that execute between the end of Lj and the beginning of Lk"
* NB: Punto 0 -> se L1 è guarded, L2 è guarded e viceversa
* NB: Di base: do_while sono non guarded, for sono guarded (inserire un do_while in un if per renderlo guarded)
* Guarded: il successore non loop (exit) della guardia L1 deve essere l'entry block di L2, ovvero il blocco della sua guardia (L2)
* Non Guarded: l'exit block di L1 deve essere il preheader di L2
**/
bool areAdjacent(Loop &L1, Loop &L2){

  //Controllo che i due Loop siano adiacenti
  bool blocksAdjacent = (L1.isGuarded() && getExitGuardSuccessor(L1) == L2.getLoopGuardBranch()->getParent()) || // Guarded
  (!L1.isGuarded() && L1.getExitBlock() == L2.getLoopPreheader());

  if(blocksAdjacent){
    // Controllo che tra i due loop non ci siano istruzioni che dipendono da L1
    BasicBlock *firstL2 = L2.isGuarded() ? L2.getLoopGuardBranch()->getParent() : L2.getLoopPreheader();

    for (Instruction &I : *firstL2) {
      if (isa<BranchInst>(&I)) break; // Fino all'istruzione di branch 
      for (Value *Op : I.operands()) {
        if (Instruction *Def = dyn_cast<Instruction>(Op)) {
          if (L1.contains(Def)) {
            outs() << "-> L'istruzione " << I << " dipende da " << *Def << "\n";
            return false; // C'è un'istruzione che dipende dal Loop 1

          }
        }
      }
    }
    return true;
  }

  return false;                     
}

// Prende il successore non loop (exit) di una guardia 
// NB: La GuardBranch ha sempre due successori: il preheader del loop e il successore dell'exit block
BasicBlock* getExitGuardSuccessor(Loop &L) {
  BranchInst *guard = L.getLoopGuardBranch();
  return guard->getSuccessor(1) != L.getLoopPreheader() ? guard->getSuccessor(1) : guard->getSuccessor(0);
}



/** ----- Punto 2 ----- 
* ! "Lj and Lk must iterate the same number of times"
* 
* NB: usare Scalar Evolution
**/
bool haveSameIteration(Loop &L1, Loop &L2, ScalarEvolution &SE){
  const SCEV *S1 = SE.getBackedgeTakenCount(&L1);
  const SCEV *S2 = SE.getBackedgeTakenCount(&L2);
  
  if (isa<SCEVCouldNotCompute>(S1) || isa<SCEVCouldNotCompute>(S2)) {
    outs() << "-> Cannot compute trip count for one or both loops.\n";
    return false;
  }
  
  outs()  << "-> BackedgeTakenCount of Loop " << loop_counter   << ": " << "S1: " << *S1 << "\n";
  outs()  << "-> BackedgeTakenCount of Loop " << loop_counter   << ": " << "S2: " << *S2 << "\n";
  
  /** 
  Il confronto funziona poichè ogni loop viene analizzato e il risultato della SCEV viene memorizzato in un indirizzo di memoria. 
  Se un altro loop viene analizzato e il risultato della SCEV è lo stesso, allora l'indirizzo di memoria sarà lo stesso. 
  FROM DOCS: "We only create one SCEV of a particular shape, so pointer-comparisons for equality are legal".
  **/
  return (S1 == S2);
}


/**  ----- Punto 3 -----   
* ! "Lj and Lk must be control flow equivalent"
*
* When Lj executes Lk also executes or when Lk executes Lj also executes 
* NB: Punto 0 -> se L1 è guarded, L2 è guarded e viceversa
**/
bool isControlFlowEquivalent(Loop &L1, Loop &L2, DominatorTree &DT, PostDominatorTree &PDT) {
  // Se sono guarded: le guardie devono essere semanticamente equivalenti, altrimenti controllo *solo* dominanza/post-dominanza
  if (L1.isGuarded() && !areGuardsEqual(L1.getLoopGuardBranch(), L2.getLoopGuardBranch())){
    outs() << "-> le guardie non sono semanticamente uguali \n";
    return false;
  }

  // Se sono guarded assegno il blocco della guardia, altrimenti assengo l'header
  BasicBlock *L1_block = L1.isGuarded() ? L1.getLoopGuardBranch()->getParent() : L1.getHeader();
  BasicBlock *L2_block = L2.isGuarded() ? L2.getLoopGuardBranch()->getParent() : L2.getHeader();

  return (DT.dominates(L1_block, L2_block) && PDT.dominates(L2_block, L1_block)); // True se L1 domina L2 ed L2 postdomina L1
}

// Controlla se le due guardie sono semanticamente equivalenti
bool areGuardsEqual(BranchInst *G1, BranchInst *G2) {
  bool areEqual = false;

  // Se sono entrambi Branch Condizionali, ritorna se le condizioni sono equivalenti
  if (G1->isConditional() && G2->isConditional()) {
    auto *icmp1 = dyn_cast<ICmpInst>(G1->getCondition());
    auto *icmp2 = dyn_cast<ICmpInst>(G2->getCondition());

    areEqual = (icmp1 && icmp2 && icmp1->isIdenticalTo(icmp2)); // icmp1->isIdenticalTo, co
  }

  if (areEqual) 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are equals\n";
  else 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are NOT equals\n";
  
  return areEqual;
}


/** ----- Punto 4 ----- 
* ! "There cannot be any negative distance dependencies between Lj and Lk"
*
* A negative distance dependence occurs between Lj and Lk, Lj before Lk, when at iteration m from Lk uses 
* a value that is computed by Lj at a future iteration m+n (where n > 0).
**/
bool haveNotNegativeDependencies(Loop &L1, Loop &L2, ScalarEvolution &SE, DependenceInfo &DI) {
  return (haveNotNegativeMemoryDependencies(L1, L2, SE, DI) && haveNotNegativeScalarDependencies(L1, L2));
}

bool haveNotNegativeMemoryDependencies(Loop &L1, Loop &L2, ScalarEvolution &SE, DependenceInfo &DI) {
  // Ci serve l'indirizzo di A
  // Poi dobbiamo vedere se l'offset di A nel secondo loop è un phi o un add di un valore positivo
  // Allora non c'è distanza negativa se anche nel primo loop c'è un'istruzione con un phi o un'istruzione con lo stesso valore positivo (corrispettivamente) 
  
  for(BasicBlock* BB: L1.blocks()) {
    for(Instruction &I : *BB) {
      auto *storeGEP = dyn_cast<GetElementPtrInst>(&I);
      if (!storeGEP) continue;
      
      auto *storeInst = dyn_cast<StoreInst>(storeGEP->getNextNode()); 
      if (!storeInst) continue; // In L1 consideriamo solo Store

      for (auto &U : storeGEP->getPointerOperand()->uses()) {
        Instruction* user = dyn_cast<Instruction>(U.getUser());
        if (!user || !L2.contains(user)) continue; 

        // Accediamo allo stesso array
        auto *storeOrLoadGEP = dyn_cast<GetElementPtrInst>(user);
        if (!storeOrLoadGEP) continue;

        outs() << "   Store instruction after GEP: " << *storeGEP << "\n";
        outs() << "   Load instruction after GEP2: " << *storeOrLoadGEP << "\n";

        // NB: evitiamo di usare depends perchè la dipendenza è controllata manualmente
        // Calcoliamo la differenza tra i due valori SCEV degli ElementPtr
        const SCEV *storeSCEV = SE.getSCEVAtScope(storeGEP, &L1); // SCEV con il contesto del loop
        const SCEV *loadSCEV = SE.getSCEVAtScope(storeOrLoadGEP, &L2);
        const SCEV *Diff = SE.getMinusSCEV(loadSCEV, storeSCEV);

        // 5 -> AddExpr
        // 8 -> AddRecExpr ("dipendente dall'indice del loop")
        outs() << "   Normalized SCEV (type: " << storeSCEV->getSCEVType() << ") Store: " << *storeSCEV << "\n"; 
        outs() << "   Normalized SCEV (type: " << loadSCEV->getSCEVType() << ") Load: " << *loadSCEV << "\n";
        outs() << "   Difference SCEV (type: " << Diff->getSCEVType() << ") Diff: " << *Diff << "\n"; 

        // Preleviamo il primissimo operando, differenza i due offset 
        const SCEV *temp = Diff; 
        const SCEVConstant *ConstDiff = dyn_cast<SCEVConstant>(temp);
        
        while(!ConstDiff){
          temp = temp->operands()[0]; 
          ConstDiff = dyn_cast<SCEVConstant>(temp);
        }
        
        int offset = ConstDiff->getValue()->getSExtValue();
        outs() << "   Offset: " << offset << "\n";

        // Verifichiamo che la differenza tra le due SCEV sia una SCEVAddRecExpr
        // NB: SCEVAddRecExpr -> ricorrenza polinomiale sul trip count del ciclo specificato
        const SCEVAddRecExpr *DiffRec = dyn_cast<SCEVAddRecExpr>(Diff);
        if (!DiffRec) return false;

        const SCEV *Step = DiffRec->getStepRecurrence(SE); // Dove tra L1 e L2 dovrebbe essere uguale dato il secondo punto e nel caso stessa guardia
        const SCEVConstant *ConstStep = dyn_cast<SCEVConstant>(Step);
        if(!ConstStep) return false;

        int step = ConstStep->getValue()->getSExtValue();
        outs() << "   Step value: " << step << "\n";
      
        // Se step è negativo, allora offset negativo = dipendenza negativa
        if ((step > 0 && offset > 0) || (step < 0 && offset < 0)) {
          outs() << "-> Negative dependency found due to offset " << offset << " with step " << step << "\n";
          return false;
        }

        // Nessuna condizione negativa, quindi controlliamo le prossime istruzioni
      }  
    } 
  }

  return true;
}

// Controlla se c'è una dipendenza negativa tra scalari tra due loop (scalari)
bool haveNotNegativeScalarDependencies(Loop &L1, Loop &L2) {
  for (BasicBlock *BB2 : L2.blocks()) {
    for (Instruction &I2 : *BB2) {
      for (Value *Op : I2.operands()) {
        if (Instruction *Def = dyn_cast<Instruction>(Op)) {
          if (L1.contains(Def) && !L1.isLoopInvariant(Def)) {
            outs() << "-> Negative dependency: " << I2 << " -> depends on non-invariant: " << *Def << "\n";
            return false;
          }
        }
      }
    }
  }
  return true;
}

void printBlock(std::string s, BasicBlock *BB) {
  outs() << s << ": ";
  BB->printAsOperand(outs(), false);
  outs() << "\n";
}

void merge_guarded(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT, ScalarEvolution &SE, DependenceInfo &DI, Function &F){
  return;
}

void merge(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT, ScalarEvolution &SE, DependenceInfo &DI, Function &F){
  // Blocchi L1
  BasicBlock *guardL1 = L1->isGuarded() ? L1->getLoopGuardBranch()->getParent() : nullptr;
  BasicBlock *preHeaderL1 = L1->getLoopPreheader();
  BasicBlock *headerL1 = L1->getHeader();
  BasicBlock *latchL1 = L1->getLoopLatch();
  BasicBlock *firstBlockBodyL1 = headerL1->getTerminator()->getSuccessor(0);
  BasicBlock *lastBlockBodyL1 = latchL1->getSinglePredecessor();
  BasicBlock *exitingL1 = L1->getExitingBlock();
  BasicBlock *exitL1 = L1->getExitBlock();

  outs() << "*** L1 BLOCKS ***\n";
  printBlock("L1 PreHeader", preHeaderL1);
  printBlock("L1 Header", headerL1);
  printBlock("L1 First Block Body", firstBlockBodyL1);
  printBlock("L1 Last Block Body", lastBlockBodyL1);
  printBlock("L1 Latch", latchL1);
  printBlock("L1 Exiting Block", exitingL1);
  printBlock("L1 Exit Block", exitL1);

  // Blocchi L2
  BasicBlock *guardL2 = L2->isGuarded() ? L2->getLoopGuardBranch()->getParent() : nullptr;
  BasicBlock *preHeaderL2 = L2->getLoopPreheader();
  BasicBlock *headerL2 = L2->getHeader();
  BasicBlock *latchL2 = L2->getLoopLatch();
  BasicBlock *firstBlockBodyL2 = headerL2->getTerminator()->getSuccessor(0);
  BasicBlock *lastBlockBodyL2 = latchL2->getSinglePredecessor();
  BasicBlock *exitingL2 = L2->getExitingBlock();
  BasicBlock *exitL2 = L2->getExitBlock();

  outs() << "*** L2 BLOCKS ***\n";
  printBlock("L2 PreHeader", preHeaderL2);
  printBlock("L2 Header", headerL2);
  printBlock("L2 First Block Body", firstBlockBodyL2);
  printBlock("L2 Last Block Body", lastBlockBodyL2);
  printBlock("L2 Latch", latchL2);
  printBlock("L2 Exiting Block", exitingL2);
  printBlock("L2 Exit Block", exitL2);

  /* Sostituzione degli usi della induction variable di L2 con quella di L1 */
  PHINode *inductionVariableL1 = L1->getCanonicalInductionVariable();
  PHINode *inductionVariableL2 = L2->getCanonicalInductionVariable();
  outs() << "Induction Variable L1: " << *inductionVariableL1 << "\n";
  outs() << "Induction Variable L2: " << *inductionVariableL2 << "\n";
  inductionVariableL2->replaceAllUsesWith(inductionVariableL1);
  inductionVariableL2->eraseFromParent(); // Rimuove l'induction variable di L2
  
  // Spostamento delle istruzioni non branch dal PreHeaderL2 al preHeaderL1
  std::vector<Instruction*> instPreHeaderL2toMove;

  // Raccogli le istruzioni non-branch da spostare
  for (auto it = L2->getLoopPreheader()->begin(), end = L2->getLoopPreheader()->end(); it != end; ++it) {
    Instruction &inst = *it;
    if (!isa<BranchInst>(&inst)) {
      instPreHeaderL2toMove.push_back(&inst);
    }
  }
  
  // Sposta le istruzioni prima del terminatore del preheader di L1
  for (Instruction *inst : instPreHeaderL2toMove) {
    outs () << "Instruzione da spostare dal PreheaderL2: " << *inst << "\n";
    inst->moveBefore(L1->getLoopPreheader()->getTerminator());
  }

  if(guardL1){
    outs() << "Guardia cambiata da ";
    guardL1->getTerminator()->getSuccessor(1)->printAsOperand(outs(), false);
    outs() << " a ";
    guardL2->getTerminator()->getSuccessor(1)->printAsOperand(outs(), false);
    guardL1->getTerminator()->setSuccessor(1, guardL2->getTerminator()->getSuccessor(1)); // Se L1 è guarded, il successore della guardia di L2 diventa la guardia di L1

    // Spostamento delle istruzioni non branch dalla Guardia di L2 alla Guardia di L1
    std::vector<Instruction*> instGuardL2toMove;

    // Raccogli le istruzioni non-branch da spostare
    for (auto it = guardL2->begin(), end = guardL2->end(); it != end; ++it) {
      Instruction &inst = *it;
      if (!isa<BranchInst>(&inst)) {
        instGuardL2toMove.push_back(&inst);
      }
    }
    
    // Sposta le istruzioni prima del terminatore del preheader di L1
    for (Instruction *inst : instGuardL2toMove) {
      if(isa<PHINode>(inst)){
        // Se l'istruzione è una PHI, spostala prima della prima istruzione non PHI del preheader di L1
        inst->moveBefore(exitL2->getTerminator());
      } else {
        // Altrimenti spostala prima del terminatore della guardia di L1
        inst->moveBefore(guardL1->getTerminator());
      }
      outs () << "Instruzione da spostare dalla Guardia di L2: " << *inst << "\n";
      
    }
  }

  // Per ora abbiamo:
  // 1) sostituito l'induction variable di L2 con quella di L1
  // 2) spostato tutte le istruzioni non-branch dal preheader di L2 al preheader di L1

  // Creiamo un branch diretto (incondizionato) da headerL2 al suo body
  //headerL2->getTerminator()->eraseFromParent();
  //BranchInst::Create(firstBlockBodyL2, headerL2);
  
  // Sostituiamo nei PHI il blocco del Preheader di L2 con quello di L1
  // NB: lo facciamo appositamente prima di spostare eventuali istruzioni dall'headerL2 all'headerL1 per avere i valori corretti
  preHeaderL2->replaceSuccessorsPhiUsesWith(preHeaderL1);
  latchL2->replaceSuccessorsPhiUsesWith(latchL1);

  //Spostiamo istruzioni da HeaderL2 usate al di fuori del Loop (causa: PHI)
  std::vector<Instruction*> instHeaderL2ToMove;
  for (Instruction &inst : *headerL2) {
    for (User *user : inst.users()) {
      if (Instruction *userInst = dyn_cast<Instruction>(user)) {
        if (!L2->contains(userInst))
          instHeaderL2ToMove.push_back(&inst);
      }
    }
  }

  for (Instruction *inst : instHeaderL2ToMove) {
    outs() << "Moving instruction from L2 header: " << *inst << "\n";
    if (isa<PHINode>(inst))
      inst->moveBefore(headerL1->getFirstNonPHI());
    else
      inst->moveBefore(headerL1->getTerminator());
  }

  exitingL1->getTerminator()->setSuccessor(1, exitL2);
  lastBlockBodyL1->getTerminator()->setSuccessor(0, firstBlockBodyL2);
  lastBlockBodyL2->getTerminator()->setSuccessor(0, latchL1);


  /*
  if(guardL1){
    std::vector<Instruction*> instGuardL2toMove;

    // Raccogli le istruzioni non-branch da spostare
    for (auto it = guardL2->begin(), end = guardL2->end(); it != end; ++it) {
      Instruction &inst = *it;
      if (!isa<BranchInst>(&inst)) {
        instGuardL2toMove.push_back(&inst);
        outs() << "Instruction to move from L2 Guard: " << inst << "\n";
      }
    }
    
    // Sposta le istruzioni prima del terminatore del guard di L1
    for (Instruction *inst : instGuardL2toMove) {
      outs () << "Instruzione da spostare dal PreheaderL2: " << *inst << "\n";
      inst->moveBefore(guardL1->getTerminator());
    }

    guardL2->getTerminator()->getSuccessor(1)->printAsOperand(outs(), false);
    guardL1->getTerminator()->setSuccessor(1, guardL2->getTerminator()->getSuccessor(1));

    lastBlockBodyL1->getTerminator()->setSuccessor(0, guardL2);

    guardL2->getTerminator()->eraseFromParent();
    BranchInst::Create(preHeaderL2, guardL2);

    
  }
  else{
    lastBlockBodyL1->getTerminator()->setSuccessor(0, preHeaderL2);
  }

  headerL2->getTerminator()->eraseFromParent();
  BranchInst::Create(firstBlockBodyL2, headerL2);

  lastBlockBodyL2->getTerminator()->setSuccessor(0, latchL1);
  exitingL1->getTerminator()->setSuccessor(1, exitL2);*/

  
  
  EliminateUnreachableBlocks(F); // Elimina i blocchi non raggiungibili (preHeaderL2, headerL2, latchL2)  
  F.print(outs());
  outs() << "Merge completed.\n";
}



/**  Esecuzione del passo di analisi "LoopFusionPass"  **/ 
PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
  ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  DependenceInfo &DI = AM.getResult<DependenceAnalysis>(F);
  
  // L1 è il loop attualmente analizzato, L2 è il loop successivo a L1
  // I loop vengono visitati in reverse order (dovuto alla depth first search)
  auto L1 = LI.rbegin();
  if (L1 == LI.rend()) {
    outs() << "Function " << F.getName() << ": no loops found in the function. \n";
    return PreservedAnalyses::all();
  }
  
  outs() << "\n   *** LoopFusionPass ***   \n";
  outs() << "=== Function: " << F.getName() << " === \n\n";
  loop_counter = 1; // Inizializzo il contatore dei loop


  for (auto L2 = std::next(L1); L2 != LI.rend(); ++L1, ++L2) {
    outs() << "* Checking Loop " << loop_counter << " and Loop " << loop_counter+1 << " *\n";
    
    if(*L1 && *L2 && isLoopFusionValid(*L1, *L2, DT, PDT, SE, DI)){
      outs() << "\n" << "Loop " << loop_counter << " and Loop " << loop_counter+1 << " can be fused\n\n";
      merge (*L1, *L2, DT, PDT, SE, DI, F);
      outs() << "\n" << "Loops fused";
    }

    loop_counter++;
    outs() << "\n";
  }
  
  return PreservedAnalyses::all();
}

// Controlla la validità della LoopFusion verificando le condizioni
bool isLoopFusionValid(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT, ScalarEvolution &SE, DependenceInfo &DI) {
  // --- Punto 0 --- 
  // Ossia L1 e L2 saranno entrambi guarded oppure non guarded (mai guarded diversamente)
  outs() << "0) Loops have the guard?\n";
  if (L1->isGuarded() == L2->isGuarded())
    outs() << "=> Loop " << loop_counter << " and Loop " << loop_counter+1 << " are both equally guarded with guard: " << L1->isGuarded() << "\n";
  else return false;
  
  // --- Punto 1 ---
  outs() << "1) Are Loops Adjacent?\n";
  if (areAdjacent(*L1, *L2)) 
    outs() << "=> Loop " << loop_counter << " is adjacent with Loop " << loop_counter+1 << "\n";
  else return false;

    // --- Punto 2 ---
  outs() << "2) Trip Count Check?\n";
  if(haveSameIteration(*L1, *L2, SE)) 
    outs() << "=> Loop " << loop_counter << " and Loop " << loop_counter+1 << " have the same iteration count\n";
  else return false;

  // --- Punto 3 ---
  outs() << "3) There is the Control Flow Equivalence?\n";
  if(isControlFlowEquivalent(*L1, *L2, DT, PDT)) 
    outs() << "=> Loop " << loop_counter << " control flow equivalent with Loop " << loop_counter+1 << "\n";
  else return false;

  // --- Punto 4 ---
  outs () << "4) Do Loops have negative dependencies?\n";
  if(haveNotNegativeDependencies(*L1, *L2, SE, DI)) 
    outs() << "=> Loop " << loop_counter << " and " << loop_counter+1 << " have no negative dependencies \n";
  else return false;

  return true;
}