#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Algebraic Identity
struct AlgebraicIdentityPass : PassInfoMixin<AlgebraicIdentityPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};

// Strength Reduction
struct StrengthReductionPass : PassInfoMixin<StrengthReductionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};

// Multi Instruction
struct MultiInstructionPass : PassInfoMixin<MultiInstructionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};
