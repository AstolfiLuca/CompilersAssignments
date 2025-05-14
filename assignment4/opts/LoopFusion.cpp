//-----------------------------------------------------------------------------
// Loop Fusion implementation
//-----------------------------------------------------------------------------


#include "LocalOpts.h"
#include <llvm/ADT/SetVector.h>
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/PostDominators.h"

int loop_counter = 1;

bool isAdjacentLoops(Loop *L1, Loop *L2){
  BasicBlock *exitBlockL1 = L1->getExitBlock();
  if (L1->isGuarded()) {
    outs() << "Loop " << loop_counter << " is guarded\n";
    if (exitBlockL1 == L2->getHeader())        // Exit Block di L1 è uguale all'header di L2
      return true;
  } else {
    outs() << "Loop " << loop_counter << " is not guarded\n";
    if(exitBlockL1 == L2->getLoopPreheader())  // Exit block di L1 è uguale al preheader di L2
      return true;
  }

  return false;
}

bool isControlFlowEquivalence(Loop *L1, Loop *L2, DominatorTree &DT, PostDominatorTree &PDT) {
  bool dominance = DT.dominates(L1->getHeader(), L2->getHeader());
  if(dominance){
    outs() << "\nL1 dominates L2\n";
  }
  else{
    outs() << "\nL1 does not dominate L2\n";
    return false;
  }

  bool postDominance = PDT.dominates(L2->getHeader(), L1->getHeader());
  if(postDominance){
    outs() << "\nL2 post dominates L1\n";
  }
  else{
    outs() << "\nL2 does not post dominate L1\n";
    return false;
  }

  return true;
}

PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

  // L1 è il loop attualmente analizzato, L2 è il loop successivo a L1
  // I loop vengono visitati al contrario
  for (auto L1 = LI.rbegin(), L2 = std::next(L1); L2 != LI.rend(); ++L1, ++L2) {
    bool isA = isAdjacentLoops(*L1, *L2); // Dereferenzia gli iteratori per ottenere Loop*
    outs() << "-> Loop " << loop_counter << " adjacent: " << isA << "\n";
    loop_counter++;
  }
  
  return PreservedAnalyses::all();
}
