#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/BasicBlock.h"

using namespace llvm;

namespace {
  struct itrBB : public FunctionPass {
    static char ID;
    itrBB():FunctionPass(ID){}

    bool runOnFunction(Function &F) {
      errs() << "Function : " << F.getName() << "\n";
      errs() << "\n";

      for(BasicBlock &BB : F){
        errs() << "BasicBlock : " << BB.getName() << "\nInstructions Size : " << BB.size() << "\n";
        
        for(Instruction &I : BB) {
          errs() << "Instruction : " << I << "\n";
        }
        errs() << "\n";
      }
      return false;
    }
  };
}

char itrBB::ID = 0;
static RegisterPass<itrBB> X("itrBB", "Iterate over the basic block inside a function");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new itrBB()); });

    // for (BasicBlock &BB : F) {  // name a basic block
    //     if (!BB.hasName())
    //       BB.setName("bb");
    //   }