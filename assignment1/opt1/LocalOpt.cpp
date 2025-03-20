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

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {
    for(Instruction &Inst : B){
      if(Inst.getOpcode() == Instruction::Add){
        auto *Op1 = Inst.getOperand(0);
        auto *Op2 = Inst.getOperand(1);

        // Se uno dei due operandi è zero, l'istruzione è inutile
        if (ConstantInt *Op = dyn_cast<ConstantInt>(Op1)) {
          if (Op->isZero() && isa<Instruction>(Op2)) {
            Inst.replaceAllUsesWith(Op2);
          }
        } else if (auto *Op = dyn_cast<ConstantInt>(Op2)) {
          if (Op->isZero() && isa<Instruction>(Op1)) {
            Inst.replaceAllUsesWith(Op1);
          }
        }
      }

      // Multiplication
      else if(Inst.getOpcode() == Instruction::Mul){
        auto *Op1 = Inst.getOperand(0);
        auto *Op2 = Inst.getOperand(1);

        // If one of the operators is 1 the instruction is useless
        if (ConstantInt *Op = dyn_cast<ConstantInt>(Op1)) {
          if (Op->isOne() && isa<Instruction>(Op2)) {
            Inst.replaceAllUsesWith(Op2);
          }
        } else if (auto *Op = dyn_cast<ConstantInt>(Op2)) {
          if (Op->isOne() && isa<Instruction>(Op1)) {
            Inst.replaceAllUsesWith(Op1);
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
