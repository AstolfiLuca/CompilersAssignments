//-----------------------------------------------------------------------------
// Multi-Instruction Optimization Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

bool isOppositeInstr(int opcode, int opcode2){
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
      int originalOpCode = Inst.getOpcode();  // Codice operazione istruzione originale
      auto *originalOp1 = Inst.getOperand(0); // 1° Operando
      auto *originalOp2 = Inst.getOperand(1); // 2° Operando
      
      auto *originalNumber = ConstantInt::get(Inst.getType(), 0); // Operando numerico
      Instruction *usedInst; // Operando istruzione (istruzione usata)
      bool isOriginalFirstOpNumber = true; // Booleano true se il primo operando è un numero, false altrimenti
      
      if (originalNumber = dyn_cast<ConstantInt>(originalOp1)) usedInst = dyn_cast<Instruction>(originalOp2);   
      else if (originalNumber = dyn_cast<ConstantInt>(originalOp2)){
        usedInst = dyn_cast<Instruction>(originalOp1);      
        isOriginalFirstOpNumber = false; // 2° Operando
      }
      if(!usedInst || !originalNumber) continue; // Se non c'è un operando istruzione, vado avanti
      
      int originalOpValue = cast<ConstantInt>(originalNumber)->getSExtValue();

      // Istruzione usata
      int usedOpCode = usedInst->getOpcode();
      auto *usedOp1 = usedInst->getOperand(0);
      auto *usedOp2 = usedInst->getOperand(1);

      auto *usedNumber = ConstantInt::get(Inst.getType(), 0);
      Value *usedInstOp; // Tipo Value per comprendere anche i parametri (oltre alle istruzioni)
      bool isUsedFirstOpNumber = true;
      if (usedNumber = dyn_cast<ConstantInt>(usedOp1)) usedInstOp = usedOp2;   
      else if (usedNumber = dyn_cast<ConstantInt>(usedOp2)){
        usedInstOp = usedOp1; 
        isUsedFirstOpNumber = false;
      }
      if(!usedInstOp || !usedNumber) continue;

      int usedOpValue = cast<ConstantInt>(usedNumber)->getSExtValue();
      
      bool optimize = false;
      if (isOppositeInstr(usedOpCode, originalOpCode) && usedOpValue == originalOpValue){
        optimize = true;
        if(originalOpCode == Instruction::Sub && isOriginalFirstOpNumber) optimize = false;
        if(usedOpCode == Instruction::Sub && isUsedFirstOpNumber) optimize = false;
      } 
      else
        if(usedOpCode == originalOpCode && originalOpCode != Instruction::SDiv){
          if (originalOpCode == Instruction::Add && (usedOpValue + originalOpValue == 0))  
            optimize = true;
          else 
            if(originalOpCode == Instruction::Sub && usedOpValue == originalOpValue)
              optimize = true;
        }

      if(optimize) Inst.replaceAllUsesWith(usedInstOp);
        
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
