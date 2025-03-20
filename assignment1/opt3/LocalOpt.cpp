//=============================================================================
// FILE:
//    LocalOpt.cpp
//
// DESCRIPTION:
//    Visits all functions in a module and prints their names. Strictly speaking, 
//    this is an analysis pass (i.e. //    the functions are not modified). However, 
//    in order to keep things simple there's no 'print' method here (every analysis 
//    pass should implement it).
//
// USAGE:
//    New PM
//      opt -load-pass-plugin=<path-to>libLocalOpt.so -passes="test-pass" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

using namespace llvm;

#include <queue>

bool runOnBasicBlock(BasicBlock &BB) {
  for (Instruction &Inst : BB) {
    if (Inst.getOpcode() == Instruction::Add) {
      // b = a + 1
      auto *Op1 = Inst.getOperand(0);
      auto *Op2 = Inst.getOperand(1);

      // Non ottimizziamo se ci sono due numeri
      if (dyn_cast<ConstantInt>(Op1) && dyn_cast<ConstantInt>(Op2)) break;

      // Non ottimizziamo se ci sono due registri
      if (!(dyn_cast<ConstantInt>(Op1) || dyn_cast<ConstantInt>(Op2))) break;

      // Queue to store the uses of instructions
      std::queue<Use *> useQueue;

      // Add initial uses of the instruction
      for (auto Uses = Inst.use_begin(); Uses != Inst.use_end(); ++Uses) {
        useQueue.push(&*Uses);
      }

      // Process the queue
      while (!useQueue.empty()) {
        Use *OpUse = useQueue.front();
        useQueue.pop();

        // Caso Store
        if (auto *storeOp = dyn_cast<StoreInst>(OpUse->getUser())) {
          auto ptrStore = storeOp->getOperand(1);

          // Add uses of the store operand
          for (auto storeUses = ptrStore->use_begin(); storeUses != ptrStore->use_end(); ++storeUses) {
            useQueue.push(&*storeUses);
          }

          // Caso Load
        } else if (auto *loadOp = dyn_cast<LoadInst>(OpUse->getUser())) {
          auto ptrLoad = loadOp->getOperand(0);

          // Add uses of the load operand
          for (auto loadUses = ptrLoad->use_begin(); loadUses != ptrLoad->use_end(); ++loadUses) {
            useQueue.push(&*loadUses);
          }

          // c = b - 1, ovvero l'operazione che usa b
          if (auto *Op = dyn_cast<Instruction>(OpUse->getUser())) {
            if (Op->getOpcode() == Instruction::Sub) {
              // Non valutiamo l'operando 0 perchè renderebbe la variabile negativa (es. non deve succedere 1 - b)
              auto Op2use = Op->getOperand(1);
              if (auto num = dyn_cast<ConstantInt>(Op2use)) {
                Value* registro = nullptr;
                bool trovato = false;

                if (num == dyn_cast<ConstantInt>(Op1)){
                  registro = Op2;
                  trovato = true;
                } else if (num == dyn_cast<ConstantInt>(Op2)){
                  registro = Op1;
                  trovato = true;
                }

                if (trovato) { // troviamo la "a"
                  // dobbiamo convertire c = b -1 -> c = a

                  // Creazione di un'allocazione di memoria per Op1
                  IRBuilder<> Builder(&Inst); // Usa IRBuilder per semplificare l'inserimento
                  AllocaInst *Alloca = Builder.CreateAlloca(Op1->getType());

                  // Creazione dell'istruzione Store
                  Instruction *NewInst = Builder.CreateStore(num, Alloca);

                  // Inserisci la nuova istruzione dopo l'istruzione corrente
                  NewInst->insertAfter(&Inst);
                }
              }
            }
          }
        }
      }
    }
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


//-----------------------------------------------------------------------------
// LocalOpt implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep everything in an anonymous namespace.
namespace {


// New PM implementation
struct LocalOpt: PassInfoMixin<LocalOpt> {
  // Main entry point, takes IR unit to run the pass on (&F) and the corresponding pass manager (to be queried if need be)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {

  	errs() << F.getName();

    if(runOnFunction(F))
      errs() << "Transformed\n";
    else
      errs() << "Not Transformed\n";
    

  	return PreservedAnalyses::all();
}


  // Without isRequired returning true, this pass will be skipped for functions
  // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
  // all functions with optnone.
  static bool isRequired() { return true; }
};
} // namespace

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getTestPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LocalOpt", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "local-opt") {
                    FPM.addPass(LocalOpt());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will be able to recognize LocalOpt when added to the pass pipeline on the command line, i.e. via '-p local-opt'
extern "C" LLVM_ATTRIBUTE_WEAK::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getTestPassPluginInfo();
}
