//-----------------------------------------------------------------------------
// Loop Fusion implementation
//-----------------------------------------------------------------------------


#include "LocalOpts.h"
#include <llvm/ADT/SetVector.h>
#include <llvm/Analysis/LoopInfo.h>
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/PostDominators.h"

bool isAdjacentLoops(Loop *L1, Loop *L2){
  outs() << "\nProcessing BasicBlock from L1: ";
  for (BasicBlock *BB1 : L1->blocks()) {
    outs() << "\n";
    BB1->printAsOperand(outs(), false);
  }
  
  outs() << "\nProcessing BasicBlock from L2: ";
  for (BasicBlock *BB2 : L2->blocks()) {
    outs() << "\n";
    BB2->printAsOperand(outs(), false);
  }

  BasicBlock *exitBlockL1 = L1->getExitBlock();
  if(L2->isGuarded()) outs() << "\nL2 is guarded\n";
  else outs() << "\nL2 is not guarded\n";

  if(L1->isGuarded()){
    outs() << "\nL1 is guarded\n";
     
    BasicBlock *HeaderBlockL2 = L2->getHeader();
    if(exitBlockL1 == HeaderBlockL2)   // Exit block di L1 è uguale al header di L2
      return true;
  }
  else{
    outs() << "\nL1 is not guarded\n";
    BasicBlock *preHeaderBlockL2 = L2->getLoopPreheader();
    if(exitBlockL1 == preHeaderBlockL2)   // Exit block di L1 è uguale al preheader di L2
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
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
  PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);
  
  for (auto it = LI.rbegin(); it != LI.rend(); ++it) {
    Loop *L1 = *it;
    auto nextIt = std::next(it);
    if (nextIt == LI.rend()){
      outs() << "No more loops to process.\n";
      break;
    }

    Loop *L2 = *nextIt;
    outs() << "Processing loops: ";

    bool isA = isAdjacentLoops(L1, L2);
    outs() << " Loop adjacet: " << isA << "\n";

    //bool isCFE = isControlFlowEquivalence(L1, L2, DT, PDT);
    //outs() << " Control flow equivalence: " << isCFE << "\n";

    // Process L1 and L2
  }

  return PreservedAnalyses::all();
}
