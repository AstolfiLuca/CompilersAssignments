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
  outs() << "1) Are Adjacent Loops\n";
  return (L1.isGuarded() && getExitGuardSuccessor(L1) == L2.getLoopGuardBranch()->getParent()) || // Guarded
         (!L1.isGuarded() && L1.getExitBlock() == L2.getLoopPreheader());                         // Non Guarded
}


/** ----- Punto 2 ----- 
* ! Lj and Lk must iterate the same number of times
* 
* NB: usare Scalar Evolution
**/
bool haveSameIteration(Loop &L1, Loop &L2, ScalarEvolution &SE){
  // Loop 1
  const SCEV *S1 = SE.getBackedgeTakenCount(&L1);
  const SCEV *S2 = SE.getTripCountFromExitCount(SE.getExitCount(&L1, L1.getExitBlock()));
  outs() << "-> BackedgeTakenCount of Loop " << loop_counter     << ": " << *S1 << "\n";
  outs() << "-> TripCount of Loop " << loop_counter     << ": " << *S2 << "\n";
  // Loop 2
  S1 = SE.getBackedgeTakenCount(&L2);
  S2 = SE.getTripCountFromExitCount(SE.getExitCount(&L2, L2.getExitBlock()));
  outs() << "-> BackedgeTakenCount of Loop " << loop_counter+1     << ": " << *S1 << "\n";
  outs() << "-> TripCount of Loop " << loop_counter+1     << ": " << *S2 << "\n";
  return false;
}


/**  ----- Punto 3 -----   
* ! Lj and Lk must be control flow equivalent
*
* When Lj executes Lk also executes or when Lk executes Lj also executes 
* NB: Punto 0 -> se L1 è guarded, L2 è guarded e viceversa
**/
bool isControlFlowEquivalent(Loop &L1, Loop &L2, DominatorTree &DT, PostDominatorTree &PDT) {
  outs() << "2) Control Flow Equivalence\n";

  // Se un loop è guarded assegno il blocco della guardia, altrimenti assengo l'header
  BasicBlock *L1_block = L1.isGuarded() ? L1.getLoopGuardBranch()->getParent() : L1.getHeader();
  BasicBlock *L2_block = L2.isGuarded() ? L2.getLoopGuardBranch()->getParent() : L2.getHeader();

  // Se sono guarded, le guardie devono essere semanticamente equivalenti, altrimenti controllo *solo* dominanza/post-dominanza
  return ((L1.isGuarded() && areGuardsEqual(L1.getLoopGuardBranch(), L2.getLoopGuardBranch())) || !L1.isGuarded()) && 
          (DT.dominates(L1_block, L2_block) && PDT.dominates(L2_block, L1_block)); // true = L1 domina L2 ed L2 postdomina L1 
}


/** ----- Punto 4 ----- 
* ! There cannot be any negative distance dependencies between Lj and Lk
*
* A negative distance dependence occurs between Lj and Lk, Lj before Lk, when at iteration m from Lk uses 
* a value that is computed by Lj at a future iteration m+n (where n > 0).
**/
bool haveNotNegativeDependencies(Loop &L1, Loop &L2){
  return true;
}


/**  Controlla la validità della LoopFusion verificando le condizioni  **/ 
bool isLoopFusionValid(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT, ScalarEvolution &SE) {
  // --- Punto 0 --- 
  // Ossia L1 e L2 saranno entrambi guarded oppure non guarded (mai guarded diversamente)
  if (L1->isGuarded() == L2->isGuarded())
    outs() << "0) Loop " << loop_counter << " and Loop " << loop_counter+1 << " are both equally guarded with guard: " << L1->isGuarded() << "\n";
  else return false;
  
  // --- Punto 1 ---
  if (areAdjacent(*L1, *L2)) 
    outs() << "1) Loop " << loop_counter << " is adjacent with Loop " << loop_counter+1 << "\n";
  else return false;

  // --- Punto 2 ---
  if(haveSameIteration(*L1, *L2, SE)) 
    outs() << "3) Loop " << loop_counter << " trip count is equal to Loop " << loop_counter+1 << " trip count\n";
  else return false;

  // --- Punto 3 ---
  if(isControlFlowEquivalent(*L1, *L2, DT, PDT)) 
    outs() << "2) Loop " << loop_counter << " control flow equivalent with Loop " << loop_counter+1 << "\n";
  else return false;

  // --- Punto 4 ---
  if(haveNotNegativeDependencies(*L1, *L2)) 
    outs() << "4) There aren't negative dependencies between Loop " << loop_counter << " and " << loop_counter+1 << " trip count\n";
  else return false;

  return true;
}

/**  Esecuzione del passo di analisi "LoopFusionPass"  **/ 
PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
  ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
  outs() << "\n*** LoopFusionPass ***\n\n";

  // L1 è il loop attualmente analizzato, L2 è il loop successivo a L1
  // I loop vengono visitati in reverse order (dovuto alla depth first search)
  for (auto L1 = LI.rbegin(), L2 = std::next(L1); L2 != LI.rend(); ++L1, ++L2) {
    outs() << "* Checking Loop " << loop_counter << " and Loop " << loop_counter+1 << " *\n";
    
    if(isLoopFusionValid(*L1, *L2, DT, PDT, SE)){
      outs() << "Validity) Loop " << loop_counter << " and Loop " << loop_counter+1 << " can be fused\n\n";
      // FUSE
    }

    loop_counter++;
  }
  
  return PreservedAnalyses::all();
}


/*
 ** Funzioni di utilità **
*/

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
    areEqual = (icmp1 && icmp2 &&                                 
                icmp1->getPredicate() == icmp2->getPredicate() && // getPredicate() recupera l'operatore di confronto (sgt, sge, slt, sle)
                icmp1->getOperand(0) == icmp2->getOperand(0) &&   // Se almeno una di queste condizioni è falsa, non sono equivalenti
                icmp1->getOperand(1) == icmp2->getOperand(1));     // true se equivalenti, false altrimenti
  }

  if (areEqual) 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are equals\n";
  else 
    outs() << "-> Guards of Loop " << loop_counter << "," << loop_counter+1 << " are NOT equals\n";
  
  return areEqual;
}