
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

// Funzione per controllare se un'istruzione è loop invariant
bool isLoopInvariant(SetVector<Instruction*> invariants, Loop &L, Instruction &Inst) {
  if (!Inst.isBinaryOp()) 
    return false; 

  for (Value* op : Inst.operands()) { 
    if (isa<Constant>(op) || isa<Argument>(op)) // Operando costante o argomento di funzione sono loop invariant
      continue;
    
    if (Instruction* I = dyn_cast<Instruction>(op)) { 
      if (!L.contains(I)) // Se la definizione dell'operando è esterna al loop, è loop invariant
        continue;
      else if (!isa<PHINode>(I) && invariants.contains(I)) // Se è già loop-invariant e non è un PHINode (ha una sola reaching definition)
        continue;
    }
     
    return false;
  }
  
  return true;
}

// Funzione per eseguire il code motion
bool isMovable(SetVector<Instruction*> movable, Loop &L, Instruction &I, DominatorTree &DT) {
  SmallVector<BasicBlock*> exitBB; 
  L.getExitBlocks(exitBB); //uscite del loop

  // ---------- Controllo "Dominanza delle uscite" ---------- 
  bool domExit;
  for (BasicBlock* block : exitBB){ 
    domExit = DT.dominates(I.getParent(), block);
    
    if (!domExit) 
      break;
  }
  
  // ---------- Controllo "Dead instruction" ---------- 
  // -- Se non domina tutte le uscite del loop ED è alive, non posso fare code motion --
  if (!domExit){
    for(Use &U : I.uses()){
      if (Instruction* user = dyn_cast<Instruction>(U.getUser())){ 
        // Se l'uso è al di fuori del loop, l'istruzione è alive
        if (!L.contains(user)) 
          return false;
      }
    }
  }
  
  for (Use &U : I.uses()){  
    // Se l'istruzione sta modificando una variabile interna al loop, non posso fare la code motion
    if (PHINode* phi = dyn_cast<PHINode>(U.getUser())){
      if (L.contains(phi))
        return false; // Se trovo un PHI node, allora sto usando una variabile per cui ho altre definizioni
    }

    // Se trovo un uso non dominato dal blocco dell'istruzione, non posso fare la code motion
    if(!DT.dominates(I.getParent(), U))
      return false;
  }

  return true; // Se tutte le condizioni sono soddisfatte, posso fare code motion
}

// Funzione per controllare se l'istruzione ha dipendenze non movable
// Se l'istruzione ha dipendenze non movable, non posso fare code motion
bool hasDependencies(SetVector<Instruction*> movable, Loop &L, Instruction &I) {
  for (Value* op : I.operands()) {
    if (isa<Constant>(op) || isa<Argument>(op)) // Se un operando è costante o argomento di funzione, allora non è una dipendenza
      continue;

    //Se la definizione dell'operando è nel loop e non è in movable, allora non posso fare code motion
    if (Instruction* opInst = dyn_cast<Instruction>(op)) {
      if (!movable.contains(opInst) && L.contains(opInst))
        return true; 
    }
  }
  return false;
}

PreservedAnalyses LoopInvariantPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);

  // Return all of the loops in the function in preorder across the loop nests, with siblings in forward program order. 
  for (Loop *L : LI.getLoopsInPreorder()) {  // Itera su tutti i loop (anche innestati)
    SmallVector<BasicBlock*> exitBB;    // Uscite del loop
    SetVector<BasicBlock*> stack;       // Pila dei blocchi da visitare
    SetVector<BasicBlock*> visited;     // Pila che memorizza i blocchi già visitati
    SetVector<Instruction*> invariants; // Istruzioni loop invariant
    SetVector<Instruction*> movable;    // Istruzioni candidate alla code motion
    
    // Inizializza le pile con il blocco header del loop
    visited.insert(L->getHeader()); 
    stack.insert(L->getHeader()); 

    // Inizializza le uscite del loop nel vettore exitBB
    L->getExitBlocks(exitBB);

    outs() << "Visiting Loop: ";
    // Depth First Search dei blocchi del Loop
    while (stack.size() > 0) {
      BasicBlock* BB = stack.pop_back_val();
      BB->printAsOperand(errs(), false); // Stampa il blocco corrente
      outs() << " | ";
      
      // Aggiorno il vettore delle istruzioni loop invariant
      for (Instruction &I : *BB){ 
        if (isLoopInvariant(invariants, *L, I))
          invariants.insert(&I); // Se l'istruzione è loop invariant, la inserisco nell'insieme
      }
        
      // Se l'istruzione è loop invariant e posso fare code motion, allora la inserisco nell'apposito vettore
      for (Instruction* I : invariants) {
        if (isMovable(movable, *L, *I, DT)) 
          movable.insert(I); 
      }
    
      // Se il blocco corrente è un'uscita del loop (quindi è contenuto in exitBB), allora non aggiungo i successori alla pila
      if (is_contained(exitBB, BB))  
        continue;

      // Aggiungo i successori del blocco corrente alla pila
      for (BasicBlock* bb : successors(BB)) {
        if (!visited.contains(bb)){
          stack.insert(bb);
          visited.insert(BB);
        }
      }
    }

    // Per ogni istruzione candidata alla code motion, controllo le sue dipendenze ed eventualmente le sposto
    for (auto it = movable.begin(), end = movable.end(); it != end; ) {
      Instruction &I = **it++;

      // Se l'istruzione ha dipendenze non movable, non posso fare code motion
      if (hasDependencies(movable, *L, I)) 
      continue;

      // Se l'istruzione è loop invariant, posso fare code motion e non ha dipendenze 
      // allora effettuo lo spostamento dell'istruzione (e la rimuovo dal vettore)
      I.moveBefore(L->getLoopPreheader()->getTerminator()); // Sposta l'istruzione alla fine del preheader
      movable.remove(&I); // Rimuovo l'istruzione dalla lista delle istruzioni da spostare e aggiorno l'iteratore
    }
    outs() << "\n";
  }
  
  outs() << "\n";
  for (Loop *L : LI.getLoopsInPreorder()) 
    outs() << "Loop Preheader: " << *L->getLoopPreheader() << "\n";
  
  return PreservedAnalyses::all();
}
