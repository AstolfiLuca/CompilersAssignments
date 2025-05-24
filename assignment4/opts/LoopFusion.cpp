//-----------------------------------------------------------------------------
// Loop Fusion implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"
#include <llvm/ADT/SetVector.h>
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/DependenceAnalysis.h"

using namespace llvm;

int loop_counter = 1; // Serve solo per l'output

// Prototipi delle funzioni di utilità
BasicBlock* getExitGuardSuccessor(Loop &L);
bool areGuardsEqual(BranchInst *G1, BranchInst *G2);


/**  ----- Punto 1 ----- 
* ! Lj and Lk must be adjacent
*
* There cannot be any statements that execute between the end of Lj and the beginning of Lk
* NB: Punto 0 -> se L1 è guarded, L2 è guarded e viceversa
* NB: Di base: do_while sono non guarded, for sono guarded (inserire un do_while in un if per renderlo guarded)
* Guarded: il successore non loop (exit) della guardia L1 deve essere l'entry block di L2, ovvero il blocco della sua guardia (L2)
* Non Guarded: l'exit block di L1 deve essere il preheader di L2
**/
bool areAdjacent(Loop &L1, Loop &L2){
  return (L1.isGuarded() && getExitGuardSuccessor(L1) == L2.getLoopGuardBranch()->getParent()) || // Guarded
         (!L1.isGuarded() && L1.getExitBlock() == L2.getLoopPreheader());                         // Non Guarded
}


/**  ----- Punto 3 -----   
* ! Lj and Lk must be control flow equivalent
*
* When Lj executes Lk also executes or when Lk executes Lj also executes 
* NB: Punto 0 -> se L1 è guarded, L2 è guarded e viceversa
**/
bool isControlFlowEquivalent(Loop &L1, Loop &L2, DominatorTree &DT, PostDominatorTree &PDT) {
  // Se sono guarded: le guardie devono essere semanticamente equivalenti, altrimenti controllo *solo* dominanza/post-dominanza
  // !areGuardsEqual(L1.getLoopGuardBranch(), L2.getLoopGuardBranch()
  if (L1.isGuarded() && !areGuardsEqual(L1.getLoopGuardBranch(), L2.getLoopGuardBranch())){
    outs() << "-> le guardie non sono semanticamente uguali \n";
    return false;
  }

  // Se sono guarded assegno il blocco della guardia, altrimenti assengo l'header
  BasicBlock *L1_block = L1.isGuarded() ? L1.getLoopGuardBranch()->getParent() : L1.getHeader();
  BasicBlock *L2_block = L2.isGuarded() ? L2.getLoopGuardBranch()->getParent() : L2.getHeader();

  return (DT.dominates(L1_block, L2_block) && PDT.dominates(L2_block, L1_block)); // True se L1 domina L2 ed L2 postdomina L1
}


/** ----- Punto 2 ----- 
* ! Lj and Lk must iterate the same number of times
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


/** ----- Punto 4 ----- 
* ! There cannot be any negative distance dependencies between Lj and Lk
*
* A negative distance dependence occurs between Lj and Lk, Lj before Lk, when at iteration m from Lk uses 
* a value that is computed by Lj at a future iteration m+n (where n > 0).
**/
bool haveNotNegativeDependencies(Loop &L1, Loop &L2, DependenceInfo &DI) {
  // Ci serve l'indirizzo di A
  // Poi dobbiamo vedere se l'offset di A nel secondo loop è un phi o un add di un valore positivo
  // Allora non c'è distanza negativa se anche nel primo loop c'è un'istruzione con un phi o un'istruzione con lo stesso valore positivo (corrispettivamente) 
  

  for(BasicBlock* BB: L1.blocks()){
    for(Instruction &I : *BB){
      // Array
      if (auto *gep = dyn_cast<GetElementPtrInst>(&I)) {
        Value *arrayPtr = gep->getPointerOperand();
        outs() << "Istruzione GEP: " << I << " con puntatore: " << *arrayPtr << "\n";

        for (auto &U : arrayPtr->uses()) {
          if (Instruction* user = dyn_cast<Instruction>(U.getUser())) {
            outs() << "Uso dell'array: " << *user << "\n";
            
            if (!L2.contains(user)) continue;

            if (auto *gep2 = dyn_cast<GetElementPtrInst>(user)){ // Accediamo allo stesso array
              Instruction *nextInst = gep->getNextNode();
              Instruction *nextInst2 = gep2->getNextNode();
              
              if (auto *storeInst = dyn_cast<StoreInst>(nextInst)) {
                if (auto *loadInst = dyn_cast<LoadInst>(nextInst2)) {
                  outs() << "Store instruction after GEP: " << *storeInst << "\n";
                  outs() << "Load instruction after GEP2: " << *loadInst << "\n";
                  std::unique_ptr<Dependence> dep = DI.depends(storeInst, loadInst, true);
                  dep->dump(outs());

                  outs() << "loop indipendent -> " << dep->isLoopIndependent() << "\n";
                  if (dep) {
                    outs() << "-> Negative distance dependency found\n";
                    return false;
                  }
                }
              }
            }
          }    
        } // Fine ciclo usi
      } 
      // Scalare
      else {
        for(Use &U : I.uses()){
          if (Instruction* user = dyn_cast<Instruction>(U.getUser())){
            // Se l'uso è nel secondo loop, controllo se ci sono dipendenze, cioè se l'istruzioe è dipendente da Loop. Se si la fusione non è valida
            if (L2.contains(user) and !L1.isLoopInvariant(&I)) {
              outs() << "-> Dependency found between " << *user << " and " << I << "\n";
              return false;
            }
          }
        }
      }
    } // Ciclo istruzioni
  } // Ciclo blocchi

  return true;
}


/**  Controlla la validità della LoopFusion verificando le condizioni  **/ 
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

  // --- Punto 3 ---
  outs() << "3) There is the Control Flow Equivalence?\n";
  if(isControlFlowEquivalent(*L1, *L2, DT, PDT)) 
    outs() << "=> Loop " << loop_counter << " control flow equivalent with Loop " << loop_counter+1 << "\n";
  else return false;
  
  // --- Punto 2 ---
  outs() << "2) Trip Count Check?\n";
  if(haveSameIteration(*L1, *L2, SE)) 
    outs() << "=> Loop " << loop_counter << " and Loop " << loop_counter+1 << " have the same iteration count\n";
  else return false;

  // --- Punto 4 ---
  outs () << "4) Do Loops have negative dependencies?\n";
  if(haveNotNegativeDependencies(*L1, *L2, DI)) 
    outs() << "=> Loop " << loop_counter << " and " << loop_counter+1 << " have no negative dependencies \n";
  else return false;

  return true;
}

/**  Esecuzione del passo di analisi "LoopFusionPass"  **/ 
PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
  ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  DependenceInfo &DI = AM.getResult<DependenceAnalysis>(F);
  outs() << "\n*** LoopFusionPass ***\n\n";

  // L1 è il loop attualmente analizzato, L2 è il loop successivo a L1
  // I loop vengono visitati in reverse order (dovuto alla depth first search)
  for (auto L1 = LI.rbegin(), L2 = std::next(L1); L2 != LI.rend(); ++L1, ++L2) {
    outs() << "* Checking Loop " << loop_counter << " and Loop " << loop_counter+1 << " *\n";
    
    if(isLoopFusionValid(*L1, *L2, DT, PDT, SE, DI)){
      outs() << "\n" << "Validity) Loop " << loop_counter << " and Loop " << loop_counter+1 << " can be fused\n\n";
      // FUSE
    }

    loop_counter++;
    outs() << "\n";
  }
  
  return PreservedAnalyses::all();
}


// ----- Funzioni di utilità -----

// Prende il successore non loop (exit) di una guardia 
// NB: La GuardBranch ha sempre due successori: il preheader del loop e il successore dell'exit block
BasicBlock* getExitGuardSuccessor(Loop &L) {
  BranchInst *guard = L.getLoopGuardBranch();
  return guard->getSuccessor(1) != L.getLoopPreheader() ? guard->getSuccessor(1) : guard->getSuccessor(0);
}


// Controlla se le due gardie sono semanticamente equivalenti
bool areGuardsEqual(BranchInst *G1, BranchInst *G2) {
  bool areEqual = false;

  // Se sono entrambi Branch Condizionali, ritorna se le condizioni sono equivalenti
  if (G1->isConditional() && G2->isConditional()) {
    auto *icmp1 = dyn_cast<ICmpInst>(G1->getCondition());
    auto *icmp2 = dyn_cast<ICmpInst>(G2->getCondition());

    areEqual = (icmp1 && icmp2 && icmp1->isIdenticalTo(icmp2));
  }

  if (areEqual) 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are equals\n";
  else 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are NOT equals\n";
  
  return areEqual;
}