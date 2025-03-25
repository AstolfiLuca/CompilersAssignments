#include "LocalOpts.h"

bool add_passes(StringRef Name, FunctionPassManager &FPM){
  if (Name == "ai") {
    FPM.addPass(AlgebraicIdentityPass());
    return true;
  }
  if (Name == "sr") {
    FPM.addPass(StrengthReductionPass());
    return true;
  }
  if (Name == "mi") {
    FPM.addPass(MultiInstructionPass());
    return true;
  }

  return false;
}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getTestPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "LocalOpt", LLVM_VERSION_STRING, [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback([](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
          return add_passes(Name, FPM);
        }
      );
    }
  };
}

// This is the core interface for pass plugins. It guarantees that 'opt' will be able to recognize LocalOpt when added to the pass pipeline on the command line, i.e. via '-p local-opt'
extern "C" LLVM_ATTRIBUTE_WEAK::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getTestPassPluginInfo();
}