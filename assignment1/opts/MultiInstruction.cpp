//-----------------------------------------------------------------------------
// Multi-Instruction Optimization Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

bool runOnBasicBlockOpt3(BasicBlock &BB) {
  for (Instruction &Inst : BB) {
    if (Inst.getOpcode() == Instruction::Sub) {
      auto *Op1 = Inst.getOperand(0);
      auto *Op2 = Inst.getOperand(1);

      if (auto *AddInst = dyn_cast<Instruction>(Op1)) {
        if (AddInst->getOpcode() == Instruction::Add) {
          if (AddInst->getOperand(1) == Op2) {
            Inst.replaceAllUsesWith(AddInst->getOperand(0));

          }
        }
      }
    }
  }
  return true;
}

bool runOnFunctionOpt3(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlockOpt3(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}

PreservedAnalyses MultiInstructionPass::run(Function &F, FunctionAnalysisManager &) {
  	errs() << F.getName() << ": ";

    if(runOnFunctionOpt3(F)) 
      errs() << "Transformed by MultiInstructionPass \n";
    else 
      errs() << "Not Transformed by MultiInstructionPass\n";
      
  	return PreservedAnalyses::all();
}
