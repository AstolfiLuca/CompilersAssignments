//-----------------------------------------------------------------------------
// Multi-Instruction Optimization Pass implementation
//-----------------------------------------------------------------------------

#include "LocalOpts.h"

/*
    Nota per la rilettura:
    b = a + 1; // "used" si riferisce alla seconda istruzione che controlliamo, quella usata dalla prima
    c = b - 1; // "inst" si riferisce alla prima istruzione che controlliamo (originale)
    c = a      // Risultato dell'ottimizzazione, poichè c = a + 1 - 1 = a
  */
bool isOptimizableOpt3(int instOpCode, int usedOpCode, int instNumber, int usedNumber, bool isFirstInstOpNumber, bool isFirstUsedOpNumber){
  return (
    instNumber == usedNumber && (
      (usedOpCode == Instruction::Add && instOpCode == Instruction::Sub  && !isFirstInstOpNumber) || // x = (a+3 || 3+a) ; y = x-3           => y=a 
      (usedOpCode == Instruction::Sub && instOpCode == Instruction::Add  && !isFirstUsedOpNumber) || // x = a-3          ; y = (x+3 || 3+x)  => y=a    
      (usedOpCode == Instruction::Mul && instOpCode == Instruction::SDiv && !isFirstInstOpNumber) || // x = (a*3 || 3*a) ; y = x/3           => y=a
      (usedOpCode == Instruction::Sub && instOpCode == Instruction::Sub  && isFirstInstOpNumber && isFirstUsedOpNumber) // x = 3-a ; y = 3-x => y=a
    ) || 
    instNumber == -usedNumber && (
      (usedOpCode == Instruction::Add && instOpCode == Instruction::Add) // x = (a+(-3) || (-3)+a) ; y = (x+3 || 3+x) => y=a  (e viceversa)
    )
  );
}

bool runOnBasicBlockOpt3(BasicBlock &BB) {
  for (Instruction &Inst : BB) {
    if(Inst.getOpcode() == Instruction::Add || Inst.getOpcode() == Instruction::Sub || Inst.getOpcode() == Instruction::SDiv) {

      // Istruzione originale
      ConstantInt *instNumberOp; // Operando numerico dell'istruzione originale
      Instruction *Used;         // Operando registro dell'originale (istruzione usata)
      
      bool isFirstInstOpNumber;  // True se il primo operando dell'istruzione originale è un numero, false altrimenti
      
      if (instNumberOp = dyn_cast<ConstantInt>(Inst.getOperand(0))) { 
        Used = dyn_cast<Instruction>(Inst.getOperand(1));
        isFirstInstOpNumber = true;
      } 
      else if (instNumberOp = dyn_cast<ConstantInt>(Inst.getOperand(1))) {
        Used = dyn_cast<Instruction>(Inst.getOperand(0));      
        isFirstInstOpNumber = false; 
      } 
      
      if(!Used) continue; // I due operandi sono entrambi registri o numeri
      
      // Istruzione usata dall'originale
      ConstantInt *usedNumberOp; // Operando numerico
      Value *replaceRegister;    // Operando registro con cui rimpiazziamo l'originale
      bool isFirstUsedOpNumber;  // True se il primo operando dell'istruzione utilizzata è un numero, false altrimenti
      
      if (usedNumberOp = dyn_cast<ConstantInt>(Used->getOperand(0))) { // Controllo se il primo operando è un numero
        replaceRegister = Used->getOperand(1); // No cast perchè è un Value
        isFirstUsedOpNumber = true;
      }
      else if (usedNumberOp = dyn_cast<ConstantInt>(Used->getOperand(1))) { // Altrimenti controllo se il secondo operando è un numero
        replaceRegister = Used->getOperand(0); // No cast perchè è un Value
        isFirstUsedOpNumber = false;
      }
      
      if(!usedNumberOp) continue; // I due operandi sono entrambi registri o numeri
      
      int instNumber = cast<ConstantInt>(instNumberOp)->getSExtValue(); // Valore del numero nell'operazione originale
      int usedNumber = cast<ConstantInt>(usedNumberOp)->getSExtValue(); // Valore del numero nell'operazione usata
      
      if(isOptimizableOpt3(Inst.getOpcode(), Used->getOpcode(), instNumber, usedNumber, isFirstInstOpNumber, isFirstUsedOpNumber)) 
        Inst.replaceAllUsesWith(replaceRegister);
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
