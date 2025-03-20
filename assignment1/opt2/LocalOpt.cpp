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

#include <cmath>

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

bool runOnBasicBlock(BasicBlock &BB) {
  for(Instruction &Inst : BB){
    if(Inst.getOpcode() == Instruction::Mul || Inst.getOpcode() == Instruction::SDiv){
      
      
      bool division = false;
      if (Inst.getOpcode() == Instruction::SDiv)
        division = true;
      
      auto *Op1 = Inst.getOperand(0);
      auto *Op2 = Inst.getOperand(1);

      auto *Op = ConstantInt::get(Inst.getType(), 0); 
      Instruction *I;
      
      if (auto *Op1Const = dyn_cast<ConstantInt>(Op1)) {
        Op = Op1Const;
        I = dyn_cast<Instruction>(Op2);
      } else if (auto *Op2Const = dyn_cast<ConstantInt>(Op2)) {
        Op = Op2Const;
        I = dyn_cast<Instruction>(Op1);
      }

      int x = cast<ConstantInt>(Op)->getSExtValue();
      bool powerOfTwoMinus1 = !(x-1 == 0) && !(x-1 & (x-1 - 1)); 
      bool powerOfTwo       = !(x   == 0) && !(x   & (x   - 1));
      bool powerOfTwoPlus1  = !(x+1 == 0) && !(x+1 & (x+1 - 1)); 

      Instruction *NewInst;

      if(powerOfTwo || powerOfTwoMinus1 || powerOfTwoPlus1){
        int pot = static_cast<int>(log2(x));
        if(powerOfTwoPlus1) pot++;

        BinaryOperator *Shift;

        if(division){
          Shift = BinaryOperator::Create(
            Instruction::LShr, I, ConstantInt::get(I->getType(), pot)
          );
        }else{
          Shift = BinaryOperator::Create(
            Instruction::Shl, I, ConstantInt::get(I->getType(), pot)
          );
        }

        

        Shift->insertAfter(&Inst);
        NewInst = Shift;
        
        if(powerOfTwoMinus1 && !division){
          auto *AddInst = BinaryOperator::Create(
            Instruction::Add, Shift, I
          );

          AddInst->insertAfter(Shift);
          NewInst = AddInst;
        }

        if(powerOfTwoPlus1 && !division){
          auto *SubInst = BinaryOperator::Create(
            Instruction::Sub, Shift, I
          );

          SubInst->insertAfter(Shift);
          NewInst = SubInst;
        }
        Inst.replaceAllUsesWith(NewInst);
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
