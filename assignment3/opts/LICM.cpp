
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
  for (Value* op : Inst.operands()) { 
    // Sono loop invariant gli operandi costanti o argomenti di funzione
    if (isa<Constant>(op) || isa<Argument>(op)) continue;
    
    // L'operando è loop invariant se la sua definizione è esterna la loop,
    // oppure se dentro al loop, non è un PHINode ed è loop invariant 
    if (Instruction* I = dyn_cast<Instruction>(op)) { 
      if (!L.contains(I) || (!isa<PHINode>(I) && invariants.contains(I))) 
        continue; // l'operando è loop invariant 
    }
     
    return false;
  }
  
  return true;
}

// Funzione per eseguire la code motion
bool isMovable(DominatorTree &DT, Loop &L, Instruction &I) {
  SmallVector<BasicBlock*> exitBB; 
  L.getExitBlocks(exitBB); // Uscite del loop inserite in exitBB
  
  outs() << " - Istruzione: " << I << " -> ";

  // ---------- Controllo "Dominanza delle uscite" ---------- 
  bool domExit;
  for (BasicBlock* block : exitBB){ 
    domExit = DT.dominates(I.getParent(), block); // getParent() restituisce il blocco dell'istruzione
    
    if (!domExit) 
      break;
  }
  
  /* ---------- Controllo per procedere: "Dead instruction" ---------- 
    SI Code motion se: 
      "Si trovano in blocchi che dominano tutte le uscite del loop" OPPURE  
      "la variabile definita dall'struzione è dead all'uscita del loop"
      
    NO code motion, al contrario, se: 
      Se non domina tutte le uscite del loop ED è alive */

  if (!domExit){
    for(Use &U : I.uses()){
      if (Instruction* user = dyn_cast<Instruction>(U.getUser())){ 
        // Se ogni uso è al di fuori del loop, l'istruzione è alive (altrimenti è morta)
        if (!L.contains(user)){
          outs() << "domExit: " << domExit << "\n";
          return false;
        }
      }
    }
  }
  
  for (Use &U : I.uses()){  
    // "Assegnano un valore a variabili non assegnate altrove nel loop"
    // Se l'istruzione usata ha più di una definizione interna al loop, non posso fare la code motion
    if (PHINode* phi = dyn_cast<PHINode>(U.getUser())){
      if (L.contains(phi)){
        outs() << "more reaching definintions \n";
        return false; // Se trovo un PHI node nel loop, allora sto usando una variabile per cui ho altre definizioni
      }
    }

    // "Si trovano in blocchi che dominano tutti i blocchi nel loop che usano la variabile a cui si sta assegnando un valore"
    // Per fare la code motion, il blocco dell'istruzione deve dominare ogni suo uso
    if(!DT.dominates(I.getParent(), U)){
      outs() << "don't dominate all uses \n";
      return false; // Se trovo un uso non dominato dal blocco dell'istruzione, non posso fare la code motion
    }
  }

  outs() << " is movable \n";
  return true; // Se tutte le condizioni sono soddisfatte, posso fare code motion
}

// Funzione per controllare se l'istruzione ha dipendenze non moved (caso in cui non posso fare code motion)
bool hasDependencies(SetVector<Instruction*> moved, Loop &L, Instruction &I) {
  for (Value* op : I.operands()) {
    if (isa<Constant>(op) || isa<Argument>(op)) // Se un operando è costante o argomento di funzione, allora non è una dipendenza
      continue;

    //Se la definizione dell'operando è nel loop e non è stato spostato, allora non posso fare code motion
    if (Instruction* opInst = dyn_cast<Instruction>(op)) {
      if (L.contains(opInst) && !moved.contains(opInst))
        return true; 
    }
  }

  return false; // Se non trovo dipendenze non moved, posso fare la code motion
}

PreservedAnalyses LoopInvariantCodeMotionPass::run(Function &F, FunctionAnalysisManager &AM) {
  LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
  DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);

  // Cicla sui loop (solo quelli esterni)
  for (Loop *L : LI) {   
    SetVector<Instruction*> invariants;       // Istruzioni loop invariant
    SetVector<Instruction*> movable;          // Istruzioni candidate alla code motion
    SetVector<Instruction*> moved;            // Istruzioni spostate
    SmallVector<BasicBlock*> exitBB;          // Uscite del loop (blocchi già fuori dal Loop)
    L->getExitBlocks(exitBB);                 // Metodo per ottenere le uscite del Loop

    // Iteriamo sui blocchi del Loop (è di default una Depth First Search in pre-order)
    outs() << "Loop: ";
    for (BasicBlock* BB : L->blocks()) {
      BB->printAsOperand(errs(), false); // Stampa il blocco corrente
      outs() << " | ";

      // Aggiorno il vettore delle istruzioni loop invariant
      for (Instruction &I : *BB){ 
        if (isLoopInvariant(invariants, *L, I))
          invariants.insert(&I); // Se l'istruzione è loop invariant, la inserisco nell'insieme
      }
    }

    // Se l'istruzione è loop invariant e posso fare code motion, allora la inserisco nell'apposito vettore
    outs() << "\n";
    for (Instruction* I : invariants) {
      if (isMovable(DT, *L, *I)) 
        movable.insert(I); 
    }

    outs() << "\n" << "Istruzioni loop invariant: \n";
    for (Instruction* I : invariants) 
      outs() << "  --- " << *I << "\n";
    
    outs () << "Istruzioni movable: \n";
    for (Instruction* I : movable) 
      outs() << "  --- " << *I << "\n";

    // Per ogni istruzione movable, se non ha dipendenze non moved allora faccio la code motion
    for (Instruction *I : movable) {
      if (!hasDependencies(moved, *L, *I)){
        I->moveBefore(L->getLoopPreheader()->getTerminator());  // Sposta l'istruzione alla fine del preheader (ma prima del branch)
        moved.insert(I);                                        // Aggiungo l'istruzione spostata al vettore
      }
    } 

    outs() << "Istruzioni spostate: \n";
    for (Instruction* I : moved) {
      outs() << "  --- " << *I << "\n";
    }

    //outs() << "\n Funzione aggiornata: \n";
    //F.print(outs()); // Stampa la funzione aggiornata
  }

  return PreservedAnalyses::all();
}
