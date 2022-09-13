#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Utils/Cloning.h"

using namespace llvm;

namespace {
  struct MyFlattening : public FunctionPass {
    static char ID;
    MyFlattening():FunctionPass(ID){}

    bool runOnFunction(Function &F) {
      errs() << "Function : [" << F.getName() << "]\n";
      errs() << "\n";

      for(BasicBlock &BB : F){
        if(BB.getName() == "if.then"){
        

        BasicBlock *entryBB = &BB;
        BasicBlock::iterator splitPoint = (BasicBlock::iterator)entryBB->getFirstNonPHIOrDbgOrLifetime();
        BasicBlock *trueBB = entryBB->splitBasicBlock(++splitPoint, "trueBB");
        

        errs() << "BasicBlock : [" << BB.getName() << "]\nInstructions Size : [" << BB.size() << "]\n";
        
        for(Instruction &I : BB) {
          errs() << "Instruction : [" << I << "]\n";
        }
        errs() << "\n";


        errs() << "trueBB :[" << *trueBB << "]\n";

        }
      }

      return false;
    }
  };
}

char MyFlattening::ID = 0;
static RegisterPass<MyFlattening> X("MyFlattening", "Control Flow Flattening");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new MyFlattening()); });
    