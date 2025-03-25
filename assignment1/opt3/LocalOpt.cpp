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


bool runOnBasicBlock(BasicBlock &BB) {
  for (Instruction &Inst : BB) {
    if (!isa<BinaryOperator>(&Inst)) continue;
    auto *Op1 = Inst.getOperand(0);
    auto *Op2 = Inst.getOperand(1);
    bool isSub = (Inst.getOpcode() == Instruction::Sub);
    bool isMul = (Inst.getOpcode() == Instruction::Mul);
    
    // Controlla se è del tipo c = a - 1
    if (isSub || isMul) {
      
      for (auto Use = Inst.use_begin(); Use != Inst.use_end(); ++Use){
        errs() << "\n INST: " << Inst << " | USE: " << *(dyn_cast<Instruction>(Use->getUser())) << "\n";
      }

      //ConstantInt *intOp2 = dyn_cast<ConstantInt>(Op2);
      //if(!intOp2) continue;

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
