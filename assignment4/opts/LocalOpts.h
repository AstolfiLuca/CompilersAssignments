#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// LICM
struct LoopFusionPass : PassInfoMixin<LoopFusionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};
