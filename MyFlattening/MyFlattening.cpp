#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Scalar.h"

using namespace llvm;

namespace {
  struct MyFlattening : public FunctionPass {
    static char ID;
    MyFlattening():FunctionPass(ID){}

    bool runOnFunction(Function &f) {
      errs() << "- Start of function [" << f.getName() << "]\n";
      if(f.getName() == "myOb"){
        for (BasicBlock &bb : f){
          errs() << "- Start of Basicblock ["<< bb.getName() << "], num of instructions ["
                    << bb.size() << "] instructions.\n";

                for(Instruction &i : bb) {
                  errs() << "Instruction : [" << i << "]\n";
                }
                errs() << "\n";
        }

        for (BasicBlock &bb : f) {

          BasicBlock *entry_bb = &bb;

          errs() << "entry_bb" << *entry_bb << "\n"; 
        }


        return false;
      }
    }
  };
}

char MyFlattening::ID = 0;
static RegisterPass<MyFlattening> X("MyFlattening", "Control Flow Flattening");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new MyFlattening()); });
    