
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
#include "llvm/IR/Dominators.h"
#include "llvm/ADT/SmallVector.h"


// Aggiorna 
void updateLoopInvariant(Instruction &Inst, Loop &L, SetVector<Instruction*> &invariant) {
  for (Value *op : Inst.operands()) { // Itero sugli operandi dell'istruzione
    if (isa<Constant>(op) || isa<Argument>(op)) // operando costante o argomento di funzione sono loop invariant
      continue;
    
    if (Instruction *I = dyn_cast<Instruction>(op)) { // è un'istruzione di qualche tipo
      if (!L.contains(I)) // esterna al loop le reaching definitions sono fuori dal loop è loop invariant
        continue;
      else if (!isa<PHINode>(I) && invariant.contains(I)) // se è già loop-invariant e non è un PHINode (ha una sola reaching definition)
        continue;
    } 
    
    return;
  }
  
  invariant.insert(&Inst); //se tutti gli operandi sono loop invariant allora anche l'istruzione è loop invariant
}



void codeMotion(Loop &L, SetVector<Instruction*> &invariant, DominatorTree &DT) {
  SmallVector<BasicBlock*> exitBB; //uscite del loop
  L.getExitBlocks(exitBB);


  outs() << "Exit blocks:\n";
  // Stampa i blocchi in exitBB
  for (BasicBlock *block : exitBB) {
    block->printAsOperand(errs(), false);
    llvm::errs() << "\n";
  }

  for (Instruction *I : invariant) {
    BasicBlock *BB = I->getParent(); // Recupera il Basic Block dell'istruzione

    bool isAlive = false; // Inizializzo a true, se trovo un uso dell'istruzione allora non è dead
    for(Use& U : I->uses()){
      if (Instruction *user = dyn_cast<Instruction>(U.getUser())){ // Controllo se l'uso è un'istruzione
        if (!L.contains(user)) { // Se l'uso è all'interno del loop, allora non è dead
          isAlive = true;
          break;
        }
      }
    }


    bool domExit = true; //rimane true solo se il blocco dell'istruzione domina tutte le uscite
    for (BasicBlock* block : exitBB){ 
      if (!domExit)
        break;
      domExit = DT.dominates(BB, block);
    }

    if(isAlive && !domExit) // Se l'istruzione è viva o non domina tutte le uscite del loop, non posso fare code motion
      continue;
        
    bool isUniqueDef = true; // Inizializzo a true, se trovo più di una reaching definition allora non è unica
    for (Use& U : I->uses()){  //Controllo se tra gli usi ho un PHI node, in tal caso sto definendo una variabile per cui ho altre definizioni
      if (PHINode *phi = dyn_cast<PHINode>(U.getUser())){ 
        if (L.contains(phi)) // Controllo che il PHI node sia all'interno del loop
          isUniqueDef = false; // Se trovo un PHI node, allora non è unica
          break;
      }
    }

    if(!isUniqueDef) // Se non è unica, non posso fare code motion
      continue;

    outs() << "Prima del dominatesAll\n"; 
    bool dominatesAll = true; // Inizializzo a true, se trovo un uso dell'istruzione che non è dominato dal blocco dell'istruzione, allora non posso fare code motion
    for(Use& U : I->uses()){
      if(!DT.dominates(BB, U)){
        dominatesAll = false; // Se l'uso non è dominato dal blocco dell'istruzione, allora non posso fare code motion
        break;
      }
    }
    outs() << "Dopo il dominatesAll\n" << dominatesAll << "\n";
    if(!dominatesAll) // Se non domina tutti gli usi, non posso fare code motion
      continue;
    

    BasicBlock *preheader = L.getLoopPreheader(); // Recupera il preheader del loop

    I->moveBefore(preheader->getTerminator()); // Sposta l'istruzione alla fine del preheader
  }    
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
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);

  for (Loop *L : LI) {
    for (BasicBlock *BB : L->blocks()) {
      for (Instruction &Inst : *BB) {
        updateLoopInvariant(Inst, *L, invariant); // Aggiorno il vettore delle istruzioni loop-invariant
      }
    }
    codeMotion(*L, invariant, DT); // Eseguo il code motion
    outs() << "Invariant instructions:\n";
  
    // Stampa il vettore delle istruzioni loop-invariant
    for (Instruction *I : invariant) {
      I->print(errs());
      llvm::errs() << "\n";
    }
  }
  
  
  

  


  return PreservedAnalyses::all();
}
