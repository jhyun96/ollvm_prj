// #include "llvm/Pass.h"
// #include "llvm/IR/Function.h"
// #include "llvm/Support/raw_ostream.h"

// #include "llvm/IR/LegacyPassManager.h"
// #include "llvm/IR/BasicBlock.h"
// #include "llvm/Transforms/IPO/PassManagerBuilder.h"

// using namespace llvm;

// namespace {
//     struct BasicPass : FunctionPass {
//         static char ID;
//         BasicPass() : FunctionPass(ID) {}

//         bool runOnFunction(Function &F) {
//             errs() << "BasicBlock's name is [" << F.getName() << "]\n";

//             for (BasicBlock &BB : F){
//                 errs() << "- Basic block name is [" << BB.getName() << "], and size of instructions is [" << BB.size() << "]\n";
//             }

//             return false;
//         }
//     };
// }

// char BasicPass::ID = 0;

// static RegisterPass<BasicPass> X("BasicPass", "Basic Pass I don't know about this...", false, false);

// static RegisterStandardPasses Y(
//     PassManagerBuilder::EP_EarlyAsPossible,
//     [](const PassManagerBuilder &Builder,
//         legacy::PassManagerBase &PM) { PM.add(new BasicPass());});

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
   struct BasicPass : public FunctionPass {
    static char ID;
    BasicPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "- Start of function [" << F.getName() << "]\n";

      for (BasicBlock &BB : F)
        errs() << "- Start of Basicblock ["<< BB.getName() << "], num of instructions ["
                   << BB.size() << "] instructions.\n";

      return false;
    }
  };
}

char BasicPass::ID = 0;
static RegisterPass<BasicPass> X("BasicPass", "Iterate over the basic block inside a function");