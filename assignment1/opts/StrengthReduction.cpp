//-----------------------------------------------------------------------------
// Strength Reduction Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"
#include <cmath>

bool runOnBasicBlockOpt2(BasicBlock &BB) {
  for(Instruction &Inst : BB) {
    bool isDiv = (Inst.getOpcode() == Instruction::SDiv);

    if(isDiv || Inst.getOpcode() == Instruction::Mul) {
      Value *reg;
      ConstantInt *intOp;
      Instruction *newInst;

      // Consideriamo presente la constant propagation (CP)

      if (intOp = dyn_cast<ConstantInt>(Inst.getOperand(1))) 
        reg = Inst.getOperand(0);
      else 
        if (intOp = dyn_cast<ConstantInt>(Inst.getOperand(0))) {
          if (isDiv) continue; // La divisione deve avere il numero deve essere al denominatore 
          
          reg = Inst.getOperand(1);
        } 

      // Se entrambe le istruzioni sono registri (e non c'è un operando numerico)
      if (!intOp)
        continue;

      int x = intOp->getSExtValue();
      bool powerOfTwoMinus1 = x > 1 && floor(log2(x-1)) == ceil(log2(x-1)); // es. x = 17 
      bool powerOfTwo       = x > 0 && floor(log2(x))   == ceil(log2(x));   // es. x = 16
      bool powerOfTwoPlus1  = x > 0 && floor(log2(x+1)) == ceil(log2(x+1)); // es. x = 15

      if(isDiv && !powerOfTwo) continue; // Se è una divisione è anche un powerOfTwo 
      
      if(powerOfTwo || powerOfTwoMinus1 || powerOfTwoPlus1) {
        int pow = floor(log2(x)) + (powerOfTwoPlus1 ? 1 : 0);
        auto *pow_value = ConstantInt::get(reg->getType(), pow); // reg->getType() -> Dimensione dell'intero (es. i32 o i64)
        
        Instruction::BinaryOps shiftType = isDiv ? Instruction::LShr : Instruction::Shl;

        BinaryOperator *Shift = BinaryOperator::Create(shiftType, reg, pow_value);
        Shift->insertAfter(&Inst);
        newInst = Shift;

        // A questo punto, se non è un powerOfTwo non è neanche una isDiv
        if(!powerOfTwo) {
          Instruction::BinaryOps opType = powerOfTwoPlus1 ? Instruction::Sub : Instruction::Add;
          auto *opInst = BinaryOperator::Create(opType, Shift, reg);
          opInst->insertAfter(Shift);
          newInst = opInst;
        }
        
        Inst.replaceAllUsesWith(newInst); // NB: replaceAllUsesWith non rimuove le istruzioni (default: dce=1)
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