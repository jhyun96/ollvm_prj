#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"

using namespace llvm;

namespace {
//   void nameInstructions(Function &F) {
//    for (auto &Arg : F.args()) {
//      if (!Arg.hasName())
//        Arg.setName("arg");
//    }
  
//    for (BasicBlock &BB : F) {
//      if (!BB.hasName())
//        BB.setName("bb");
  
//      for (Instruction &I : BB) {
//        if (!I.hasName() && !I.getType()->isVoidTy())
//          I.setName("i");
//      }
//    }
//  }

  struct getName : public FunctionPass {
    static char ID;
    getName():FunctionPass(ID){}

    virtual bool runOnFunction(Function &F) override {
      errs() << "Function : [" << F.getName() << "]\n";

      for (BasicBlock &BB : F) {
        if (!BB.hasName())
          BB.setName("BB");
      }

      for(BasicBlock &BB : F){
        errs() << "BasicBlock : [" << BB.getName() << "]\nInstructions Size : [" << BB.size() << "]\n";
        
        for(Instruction &I : BB) {
          errs() << "Instruction : [" << I << "]\n";
        }
        errs() << "\n";
      }
      return false;
    }
  };
}

char getName::ID = 0;
static RegisterPass<getName> X("getName", "Print a label name in IR");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new getName()); });

    