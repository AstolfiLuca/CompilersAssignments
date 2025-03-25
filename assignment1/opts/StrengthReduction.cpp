//-----------------------------------------------------------------------------
// Strength Reduction Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"
#include <cmath>

bool runOnBasicBlockOpt2(BasicBlock &BB) {
  for(auto it = BB.begin(), end = BB.end(); it != end; ){
    Instruction &Inst = *it++;
    bool division = (Inst.getOpcode() == Instruction::SDiv);

    if(Inst.getOpcode() == Instruction::Mul || division){
      auto *Op1 = Inst.getOperand(0);
      auto *Op2 = Inst.getOperand(1);
      auto *Op = ConstantInt::get(Inst.getType(), 0); 
      Instruction *I, *NewInst;
      
      // Una delle due è per forza un'istruzione
        // Un operazione tra due numeri viene convertita 
        // direttamente in una store del risultato (anche con -O0)
      if (Op = dyn_cast<ConstantInt>(Op1)) 
        I = dyn_cast<Instruction>(Op2);
      else if (Op = dyn_cast<ConstantInt>(Op2))
        I = dyn_cast<Instruction>(Op1);

      int x = cast<ConstantInt>(Op)->getSExtValue();
      /* 
      // Caso della moltiplicazione per zero 
      // Test dell'eliminazione della moltiplicazione
      if(x == 0) {
        Inst.replaceAllUsesWith(ConstantInt::get(Inst.getType(), 0));
        Inst.eraseFromParent();
        continue;
      }
      */
      bool powerOfTwoMinus1 = (x > 1) && !(x-1 & x-2); // x = 17 
      bool powerOfTwo       = (x > 0) && !(x & x-1);   // x = 16
      bool powerOfTwoPlus1  = (x > 0) && !(x+1 & x);   // x = 15
      if(division && !powerOfTwo) continue;

      // Se è una divisione è anche un powerOfTwo
      if(powerOfTwo || powerOfTwoMinus1 || powerOfTwoPlus1){
        int pot = static_cast<int>(log2(x)) + (powerOfTwoPlus1 ? 1 : 0);
        Instruction::BinaryOps shiftType = division ? Instruction::LShr : Instruction::Shl;
        BinaryOperator *Shift = BinaryOperator::Create(
            shiftType, I, ConstantInt::get(I->getType(), pot)
          );

        Shift->insertAfter(&Inst);
        NewInst = Shift;

        // A questo punto, se non è un powerOfTwo non è neanche una divisione
        if(!powerOfTwo){
          Instruction::BinaryOps opType = powerOfTwoMinus1 ? Instruction::Add : Instruction::Sub;
          auto *opInst = BinaryOperator::Create(opType, Shift, I);
          opInst->insertAfter(Shift);
          NewInst = opInst;
        }
        
        Inst.replaceAllUsesWith(NewInst);
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

    if (runOnFunctionOpt1(F))
        errs() << "Transformed by StrengthReductionPass\n";
    else
        errs() << "Not Transformed by StrengthReductionPass\n";

    return PreservedAnalyses::all();
}