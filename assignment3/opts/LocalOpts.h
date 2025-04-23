#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Algebraic Identity
bool runOnBasicBlockOpt1(BasicBlock &BB);
bool runOnFunctionOpt1(Function &F);

struct LoopInvariantPass : PassInfoMixin<LoopInvariantPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};
