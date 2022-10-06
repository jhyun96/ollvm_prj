#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/IR/Constant.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;
using namespace std;

namespace {
  struct tis : public FunctionPass {
    static char ID;
    tis(): FunctionPass(ID) {}

    bool runOnFunction(Function& f) {

      

      for (BasicBlock &bb : f) {
        if( bb.getName() == "entry"){
          if(isa<InvokeInst>(bb.getTerminator())){
            return false;
          }
          BasicBlock *entry_bb = &bb;
          BasicBlock::iterator split_point = (BasicBlock::iterator)entry_bb->getFirstNonPHIOrDbgOrLifetime();
          BasicBlock* splittedBasicBlock = entry_bb->splitBasicBlock(split_point, "splittedBasicBlock");

          errs() << *entry_bb << "\n";
          errs() << *splittedBasicBlock << "\n"; 
          errs() << bb << "\n";
        }       
      }
      return false;
    }
  };
}


char tis::ID = 0;
static RegisterPass<tis> X("tis", "toCompare file",false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new tis()); });
