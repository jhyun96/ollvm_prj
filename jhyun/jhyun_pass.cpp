#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

// namespace {
//     struct JhyunPass : FunctionPass {
//         static char ID;
//         JhyunPass() : FunctionPass(ID) {}

//         bool runOnFunction(Function &F) override {
//             errs() << "JhyunPass: ";
//             errs().write_escaped(F.getName()) << '\n';
//             return false;
//         }
//     };
// }

// char JhyunPass::ID = 0;

// static RegisterPass<JhyunPass> X("JhyunPass", "I am Jhyun Hello", false, false);

// static RegisterStandardPasses Y(
//     PassManagerBuilder::EP_EarlyAsPossible,
//     [](const PassManagerBuilder &Builder,
//         legacy::PassManagerBase &PM) { PM.add(new JhyunPass());});

namespace {
  struct JhyunPass : public FunctionPass {
    static char ID;
    JhyunPass() : FunctionPass(ID) {}


    virtual bool runOnFunction(Function &F) {
      errs() << "- Start of function [" << F.getName() << "]\n";

      for (BasicBlock &BB : F)
        errs() << "- Start of Basicblock ["<< BB.getName() << "], num of instructions ["
                   << BB.size() << "] instructions.\n";

      return false;
    }
  };
}

char JhyunPass::ID = 0;
static RegisterPass<JhyunPass> X("JhyunPass", "Iterate over the basic block inside a function",false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new JhyunPass()); });

