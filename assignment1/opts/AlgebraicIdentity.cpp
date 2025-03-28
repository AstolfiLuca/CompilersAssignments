
//-----------------------------------------------------------------------------
// Algebraic Identity Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

bool runOnBasicBlockOpt1(BasicBlock &BB) {
  Value *op1, *op2, *zero, *one;
  ConstantInt *intOp1, *intOp2;

  for(Instruction &Inst : BB) {
    if (Inst.isBinaryOp()) {
      zero = ConstantInt::get(Inst.getType(), 0);
      one = ConstantInt::get(Inst.getType(), 1);
      op1 = Inst.getOperand(0);
      op2 = Inst.getOperand(1);
      intOp1 = dyn_cast<ConstantInt>(op1);
      intOp2 = dyn_cast<ConstantInt>(op2);

      switch(Inst.getOpcode()) {
        case Instruction::Add:
          if (intOp1 && intOp1->isZero()) Inst.replaceAllUsesWith(op2);
          else if (intOp2 && intOp2->isZero()) Inst.replaceAllUsesWith(op1);
          break;

        case Instruction::Sub:
          if (op1 == op2) Inst.replaceAllUsesWith(zero);
          else if (intOp2 && intOp2->isZero()) Inst.replaceAllUsesWith(op1);
          break;

        case Instruction::Mul:
          if(intOp1) {
            if (intOp1->isZero()) Inst.replaceAllUsesWith(zero);
            else if (intOp1->isOne()) Inst.replaceAllUsesWith(op2);
          } 
          else if(intOp2) {
            if (intOp2->isZero()) Inst.replaceAllUsesWith(zero);
            else if (intOp2->isOne()) Inst.replaceAllUsesWith(op1);
          }
          break;

        case Instruction::SDiv:
          if (op1 == op2) Inst.replaceAllUsesWith(one);
          else if(intOp1 && intOp1->isZero()) Inst.replaceAllUsesWith(zero);
          else if(intOp2 && intOp2->isOne()) Inst.replaceAllUsesWith(op1);
          break;
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
