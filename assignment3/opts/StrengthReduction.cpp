//-----------------------------------------------------------------------------
// Strength Reduction Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"
#include <cmath>

bool runOnBasicBlockOpt2(BasicBlock &BB) {
  for(Instruction &Inst : BB) {
    bool isDiv = (Inst.getOpcode() == Instruction::SDiv);

    if(isDiv || Inst.getOpcode() == Instruction::Mul) {
      Value *I;
      ConstantInt *intOp;
      Instruction *newInst;

      if (intOp = dyn_cast<ConstantInt>(Inst.getOperand(1))) 
        I = Inst.getOperand(0);
      else if (intOp = dyn_cast<ConstantInt>(Inst.getOperand(0))) {
        if (isDiv) continue; // La divisione non può essere ottimizzata se il numero è al 1° operando
        I = Inst.getOperand(1);
      } 

      if (!I || !intOp) 
        continue;

      int x = cast<ConstantInt>(intOp)->getSExtValue();
      bool powerOfTwoMinus1 = (x > 1) && !(x-1 & x-2); // x = 17 
      bool powerOfTwo       = (x > 0) && !(x & x-1);   // x = 16
      bool powerOfTwoPlus1  = (x > 0) && !(x+1 & x);   // x = 15
      if(isDiv && !powerOfTwo) continue;

      // Se è una divisione è anche un powerOfTwo
      if(powerOfTwo || powerOfTwoMinus1 || powerOfTwoPlus1) {
        int pot = static_cast<int>(log2(x)) + (powerOfTwoPlus1 ? 1 : 0);
        auto *pot_value = ConstantInt::get(I->getType(), pot);
        Instruction::BinaryOps shiftType = isDiv ? Instruction::LShr : Instruction::Shl;
        BinaryOperator *Shift = BinaryOperator::Create(shiftType, I, pot_value);
        Shift->insertAfter(&Inst);
        newInst = Shift;

        // A questo punto, se non è un powerOfTwo non è neanche una isDive
        if(!powerOfTwo) {
          Instruction::BinaryOps opType = powerOfTwoMinus1 ? Instruction::Add : Instruction::Sub;
          auto *opInst = BinaryOperator::Create(opType, Shift, I);
          opInst->insertAfter(Shift);
          newInst = opInst;
        }
        
        Inst.replaceAllUsesWith(newInst);
      }
    }
  }
  
  return true;
}

bool runOnFunctionOpt2(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlockOpt2(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}

PreservedAnalyses StrengthReductionPass::run(Function &F, FunctionAnalysisManager &) {
    errs() << F.getName() << ": ";

    if (runOnFunctionOpt2(F))
        errs() << "Transformed by StrengthReductionPass\n";
    else
        errs() << "Not Transformed by StrengthReductionPass\n";

    return PreservedAnalyses::all();
}