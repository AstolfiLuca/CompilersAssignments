#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Algebraic Identity
bool runOnBasicBlockOpt1(BasicBlock &BB);
bool runOnFunctionOpt1(Function &F);

struct AlgebraicIdentityPass : PassInfoMixin<AlgebraicIdentityPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};

// Strength Reduction
bool runOnBasicBlockOpt2(BasicBlock &BB);
bool runOnFunctionOpt2(Function &F);

struct StrengthReductionPass : PassInfoMixin<StrengthReductionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};

// Multi Instruction
bool runOnBasicBlockOpt3(BasicBlock &BB);
bool runOnFunctionOpt3(Function &F);

struct MultiInstructionPass : PassInfoMixin<MultiInstructionPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &);
  static bool isRequired() { return true; }
};
