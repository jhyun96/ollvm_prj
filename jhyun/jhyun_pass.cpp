#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
  struct JhyunPass : public FunctionPass {
    static char ID;
    JhyunPass() : FunctionPass(ID) {}

    // vector<BasicBlock *> origBB;

    bool runOnFunction(Function &F) {
      errs() << "- Start of function [" << F.getName() << "]\n";
      

        for (BasicBlock &BB : F) {
          if(BB.getName() == "entry"){
            BasicBlock *entryBB = &BB;
            errs() << *entryBB << "\n"; 

            BasicBlock::iterator splitPosition = (BasicBlock::iterator)entryBB->getFirstNonPHIOrDbgOrLifetime();
            errs() << "splitPosition : " << *splitPosition << "\n";
            BasicBlock* SaveBB = entryBB->splitBasicBlock(splitPosition, "SaveBB");
            errs() << "SaveBB" << *SaveBB << "\n";

            

            
          }
        }

        for (BasicBlock &BB : F){
              errs() << "- Start of Basicblock ["<< BB.getName() << "], num of instructions ["
                      << BB.size() << "] instructions.\n";

              for(Instruction &I : BB) {
                errs() << "Instruction : [" << I << "]\n";
              }
              errs() << "\n";
        }

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

