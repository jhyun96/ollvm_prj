#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/BasicBlock.h"

using namespace llvm;

namespace {
  struct MyFlattening : public FunctionPass {
    static char ID;
    MyFlattening():FunctionPass(ID){}

    virtual bool runOnFunction(Function &F) override {
      errs() << " Function : [" << F.getName() << "]\n";

      for (BasicBlock &BB : F) {  // name a basic block
        if (!BB.hasName())
          BB.setName("bb");
      }

      for(BasicBlock &BB : F){
        errs() << "BasicBlock : [" << BB.getName() << "]\nInstructions Size : [" << BB.size() << "]\n";

              if (BB.getName() == "bb") {
        BasicBlock *ifthenBB = &BB;  // BasicBlock 클래스를 사용하기 위해 바꿔줌

        BasicBlock::iterator splitPoint = (BasicBlock::iterator)ifthenBB->getFirstNonPHIOrDbgOrLifetime();
        BasicBlock *trueBB = ifthenBB->splitBasicBlock(splitPoint, "trueBB");

        ifthenBB->dump();
        trueBB->dump();
        //출력
      }






        
        for(Instruction &I : BB) {
          errs() << "Instruction : [" << I << "]\n";
        }
        errs() << "\n";
      }









      return false;
    }
  };
}

char MyFlattening::ID = 0;
static RegisterPass<MyFlattening> X("MyFlattening", "Creating Control Flow Flattening by Jhyun");

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new MyFlattening()); });

    