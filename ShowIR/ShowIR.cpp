#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
  struct ShowIR:public FunctionPass {
    static char ID;
    ShowIR():FunctionPass(ID){}

    bool runOnFunction(Function &F) override {
      errs() << "ShowIR : "<< F.getName() << "\n";
      for(BasicBlock &BB : F){
        errs() << "Basic Block : " << BB << "\n";
        for(Instruction &I : BB) {
          errs() << "Instruction : " << I << "\n";
        }
      }
      return false;
    }
  };
}

char ShowIR::ID = 0;
static RegisterPass<ShowIR> X("ShowIR", "Print the IR inside a function");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new ShowIR()); });