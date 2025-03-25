//-----------------------------------------------------------------------------
// Multi-Instruction Optimization Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

bool isOpposite(int opcode, int opcode2){
  return (
    opcode == Instruction::Add && opcode2 == Instruction::Sub ||
    opcode == Instruction::Sub && opcode2 == Instruction::Add ||
    opcode == Instruction::Mul && opcode2 == Instruction::SDiv
  );
}

bool runOnBasicBlockOpt3(BasicBlock &BB) {
  for (Instruction &Inst : BB) {
    if(Inst.isBinaryOp()){
      
      // Instruzione originale
      auto *originalOp1 = Inst.getOperand(0);
      auto *originalOp2 = Inst.getOperand(1);
      
      auto *originalNumberOp = ConstantInt::get(Inst.getType(), 0); // Operando numero
      Instruction *usedInst; // Operando istruzione (istruzione usata)
      
      if (originalNumberOp = dyn_cast<ConstantInt>(originalOp1)) usedInst = dyn_cast<Instruction>(originalOp2);   
      else if (originalNumberOp = dyn_cast<ConstantInt>(originalOp2)) usedInst = dyn_cast<Instruction>(originalOp1);
      if(!usedInst) continue; // Se non c'è un operando istruzione, vado avanti
      
      // Istruzione usata
      auto *usedOp1 = usedInst->getOperand(0);
      auto *usedOp2 = usedInst->getOperand(1);

      auto *usedNumberOp = ConstantInt::get(Inst.getType(), 0); 
      Instruction *usedInstOp;
      if (usedNumberOp = dyn_cast<ConstantInt>(usedOp1)) usedInstOp = dyn_cast<Instruction>(usedOp2);   
      else if (usedNumberOp = dyn_cast<ConstantInt>(usedOp2)) usedInstOp = dyn_cast<Instruction>(usedOp1); 
      
      
      // Ottimizzazione su istruzioni opposte
      if (isOpposite(usedInst->getOpcode(), Inst.getOpcode()) && usedNumberOp == originalNumberOp)
        Inst.replaceAllUsesWith(usedInstOp);

      
      // a = b + 1 | c = -1 + a
      
    } // if binary
  } // for
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
