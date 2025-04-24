
//-----------------------------------------------------------------------------
// Loop Invariant implementation
//-----------------------------------------------------------------------------

/*
ALGORITMO: 
  • LOOP-INVARIANT:
    • Calcolare le reaching definitions
    • Markare loop-invariant se:
      • Tutte le definizioni di B e C che raggiungono l’istruzione A=B+C si trovano fuori dal loop
      • C’è esattamente una reaching definition per B e C, e si tratta di un’istruzione del loop che è stata marcata loop-invariant   
  
  • CODE MOTION:
    • Calcolare le reaching definitions
    • Trovare le istruzioni loop-invariant
    • Calcolare i dominatori del blocco dove si trovano le istruzioni loop-invariant(dominance tree)
    • Trovare le uscite del loop (i successori fuori dal loop)
    • Le istruzioni candidate alla code motion:
      • Sono loop invariant
      • Si trovano in blocchi che dominano tutte le uscite del loop OPPURE la variabile definita dall’istruzione è dead all’uscita del loop
      • Assegnano un valore a variabili non assegnate altrove nel loop
      • Si trovano in blocchi che dominano tutti i blocchi nel loop che usano la variabile a cui si sta assegnando un valore
      • Eseguire una ricerca depth-first dei blocchi
      • Spostare l’istruzione candidata nel preheader se tutte le istruzioni invarianti da cui questa dipende sono state spostate
  
  • SPOSTIAMO LE ISTRUZIONI
  
*/

#include "LocalOpts.h"
#include <llvm/ADT/SetVector.h>
#include <llvm/Analysis/LoopInfo.h>

//primitiva contains
void isLoopInvariant(Instruction &Inst, Loop &L, SetVector<Instruction*> &invariant) {
  bool isInvariant = true;
  for(auto *opIter = Inst.op_begin(); opIter != Inst.op_end(); ++opIter){  // Itero su tutti gli operandi dell'istruzione
    Value *V = opIter->get();

    if (isa<Constant>(V) || isa<Argument>(V)) //operando costante o argomento di funzione sono loop invariant
      continue;

    if (Instruction *I = dyn_cast<Instruction>(V)){ //è un'istruzione di qualche tipo
        if (!L.contains(I)) //esterna al loop le reaching definitions sono fuori dal loop è loop invariant
          invariant.insert(I);

        else if (!isa<PHINode>(I)) { // è un'istruzione non PHI
          if (invariant.contains(I)){  //se è già inserita in invariant è loop invariant
            continue;
          }
          else
            isInvariant = false; //altrimenti non è loop invariant
        }
        else isInvariant = false; //se è un PHI node non è loop invariant

      }
    else
      isInvariant = false; //altrimenti non è loop invariant

  }
  if (isInvariant) 
    invariant.insert(&Inst); //se tutti gli operandi sono loop invariant allora anche l'istruzione è loop invariant
  
    
}


bool runOnBasicBlock(BasicBlock &BB) {
  for(Instruction &Inst : BB) {

  }
  return true;
}


bool runOnFunction(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlock(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}

PreservedAnalyses LoopInvariantPass::run(Function &F, FunctionAnalysisManager &AM) {
  SetVector<Instruction*> invariant;

  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

  for (Loop *L : LI) {
    for (BasicBlock *BB : L->blocks()) {
      for (Instruction &Inst : *BB) {
        isLoopInvariant(Inst, *L, invariant); // Controllo se l'istruzione è loop invariant
      }
    }
  }
  
  // Stampa il vettore delle istruzioni loop-invariant
  for (Instruction *I : invariant) {
    I->print(errs());
    llvm::errs() << "\n";
  }
  


  return PreservedAnalyses::all();
}
