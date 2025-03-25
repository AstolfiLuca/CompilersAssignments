
//-----------------------------------------------------------------------------
// Algebraic Identity Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

bool runOnBasicBlockOpt1(BasicBlock &BB) {
  for(Instruction &Inst : BB){
    if (isa<BinaryOperator>(&Inst)){
      auto *Op1 = Inst.getOperand(0);
      auto *Op2 = Inst.getOperand(1);
      auto OpCode = Inst.getOpcode();
      ConstantInt *intOp1 = dyn_cast<ConstantInt>(Op1);
      ConstantInt *intOp2 = dyn_cast<ConstantInt>(Op2);

      // Se uno dei due operandi è 0, l'addizione è inutile
      if (OpCode == Instruction::Add) {
        if (intOp1 && intOp1->isZero()) Inst.replaceAllUsesWith(Op2);
        if (intOp2 && intOp2->isZero()) Inst.replaceAllUsesWith(Op1);
      }

      // Se uno dei due operandi è 1, la moltiplicazione è inutile
      if (OpCode == Instruction::Mul) {
        if (intOp1 && intOp1->isOne()) Inst.replaceAllUsesWith(Op2);
        if (intOp2 && intOp2->isOne()) Inst.replaceAllUsesWith(Op1);
      }
    }
  }

  return true;
}

bool runOnFunctionOpt1(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlockOpt1(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}

PreservedAnalyses AlgebraicIdentityPass::run(Function &F, FunctionAnalysisManager &) {
    errs() << F.getName() << ": ";

    if (runOnFunctionOpt1(F))
        errs() << "Transformed by AlgebraicIdentityPass\n";
    else
        errs() << "Not Transformed by AlgebraicIdentityPass\n";

    return PreservedAnalyses::all();
}