#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/IR/Constant.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;
using namespace std;

namespace {
  struct JhyunPass : public FunctionPass {
    static char ID;
    JhyunPass() : FunctionPass(ID) {}

    

    bool runOnFunction(Function &F) {
      errs() << "- Start of function [" << F.getName() << "]\n";

      for (BasicBlock &BB : F) {
          if(BB.getName() == "entry"){
            BasicBlock *entryBB = &BB;
            errs() << *entryBB << "\n"; 

            BasicBlock::iterator splitPosition = (BasicBlock::iterator)entryBB->getFirstNonPHIOrDbgOrLifetime();
            errs() << "splitPosition : " << *splitPosition << "\n\n";
            BasicBlock* SaveBB = entryBB->splitBasicBlock(splitPosition, "SaveBB");
            errs() << "[SaveBB]" << *SaveBB << "\n";
          }

      if(BB.getName() == "SaveBB") {
        BasicBlock *if_then_BB = &BB;

        BasicBlock::iterator splitPosition = (BasicBlock::iterator)if_then_BB->getFirstNonPHIOrDbgOrLifetime();
        BasicBlock *true_BB = if_then_BB->splitBasicBlock(splitPosition, "true_BB");

        errs() << "Before\n";
        errs() << "if_then_BB : " << *if_then_BB << "\n\n";

        // IntegerType *I32 = Type::getInt32Ty(F.getContext());
        // errs() << "I32 : " << *I32 << "\n\n";

        // AllocaInst* var_i = new AllocaInst(Type::getInt32Ty(F.getContext()), 0, "MyValue", if_then_BB); 
        // errs() << "var_i : " << *var_i << "\n\n";
        // LoadInst* load = new LoadInst(var_i, "asdf", true_BB);
        // new StoreInst(var_i, load->getPointerOperand(), true_BB);




        Value *LHS = ConstantInt::get(Type::getInt32Ty(F.getContext()), 1);
        Value *RHS = ConstantInt::get(Type::getInt32Ty(F.getContext()), 1);

        // BinaryOperator *op =  BinaryOperator::Create(Instruction::Add, LHS, 1, true);

        // Instruction* AddInst;

        // Instruction* SubInst = BinaryOperator(Instruction::Sub, AddInst->getOperand(0), AddInst->getOperand(1), "subtmp", AddInst);

        ICmpInst *condInstruction = new ICmpInst(if_then_BB->getFirstNonPHIOrDbgOrLifetime(), ICmpInst::ICMP_EQ, LHS, RHS, "newcond");
        
        // BasicBlock *switchBB = BasicBlock::Create(F.getContext(), "", nullptr, true_BB);
        // switchBB->moveAfter(true_BB);
        // BranchInst::Create(true_BB, true_BB, condInstruction, if_then_BB);


        // BasicBlock::iterator toRemove = if_then_BB->begin();
        // toRemove++;
        // Instruction *instToRemove = &(*toRemove);
        // instToRemove->dropAllReferences();
        // instToRemove->eraseFromParent();

        errs() << "After\n";
        errs() << "if_then_BB : " << *if_then_BB << "\n\n";
      }
    }

        //전체 IR 출력
        errs() << "===============전체 IR 출력==============\n";
        for (BasicBlock &BB : F){
              errs() << "\n - Start of Basicblock ["<< BB.getName() << "], num of instructions ["
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
static RegisterPass<JhyunPass> X("J", "Iterate over the basic block inside a function",false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new JhyunPass()); });

