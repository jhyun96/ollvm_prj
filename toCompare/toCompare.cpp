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
  struct toCompare : public FunctionPass {
    static char ID;
    toCompare(): FunctionPass(ID) {}

    BasicBlock* splitBasicBlockByLinePoint(BasicBlock* target_basicblock, string new_basicblock, int line_point) {
      BasicBlock::iterator splitLine = (BasicBlock::iterator)target_basicblock->getFirstNonPHIOrDbgOrLifetime();
      for(int count = 0; count < line_point; count++){
        splitLine++;
      }
      BasicBlock* splittedBasicBlock = target_basicblock->splitBasicBlock(splitLine, new_basicblock);
      return splittedBasicBlock;
    }

    void deleteInstructionWithPosition(BasicBlock *target_basicblock, int number_to_move) {
    BasicBlock::iterator to_remove = target_basicblock->begin();
    for (int counter = 0; counter < number_to_move; counter++) {
      to_remove++;
    }
    Instruction *inst_to_remove = &(*to_remove);
    inst_to_remove->dropAllReferences();
    inst_to_remove->eraseFromParent();
    }

    bool runOnFunction(Function& f) {

      for (BasicBlock &bb : f) {
        // entry bb에서 난독화를 진행하도록
        if (bb.getName() == "entry") {

          // BasicBlock List
          BasicBlock *entry_bb = &bb; // BasicBlock 클래스를 사용하기 위해 바꿔줌
          BasicBlock* if_then_bb = splitBasicBlockByLinePoint(entry_bb, "if_then_bb",0);
          BasicBlock *true_bb = splitBasicBlockByLinePoint(if_then_bb,"true_bb",0);
          BasicBlock *false_bb = splitBasicBlockByLinePoint(if_then_bb, "false_bb",0);
          BasicBlock *switch_bb = splitBasicBlockByLinePoint(true_bb,"switch_bb",0);
          BasicBlock *dest_bb = splitBasicBlockByLinePoint(switch_bb,"dest_bb",0);

          // entry_bb 채워넣기(변수 생성)
          IRBuilder<> builder(entry_bb);
          Value *var_retval = builder.CreateAlloca(Type::getInt32Ty(f.getContext()), nullptr, "retval");
          Value *var_i = builder.CreateAlloca(Type::getInt32Ty(f.getContext()), nullptr, "i");
          // entry_bb에 retval, i에 해당하는 변수 할당
          Value *value_0 = Constant::getNullValue(Type::getInt32Ty(f.getContext()));
          builder.CreateStore(value_0, var_i, false);
          // i 변수에 0값 넣어줌
          BranchInst::Create(if_then_bb, entry_bb);
          deleteInstructionWithPosition(entry_bb,0);
          BasicBlock::iterator to_remove = entry_bb->begin();
          Instruction* inst_to_remove = &(*to_remove); 
          // inst_to_remove -> dropAllReferences();
          inst_to_remove -> eraseFromParent();
    

          // if 조건문 생성
          IRBuilder<> builder_cond(if_then_bb);
          Value *lhs = builder_cond.CreateLoad(var_i);
          // i값을 condBB에 load
          Value *cond_instruction = builder_cond.CreateICmpSGE(lhs, value_0, "");
          // BranchInst::Create(true_bb,true_bb, cond_instruction, if_then_bb);
          BranchInst::Create(true_bb, false_bb, cond_instruction, if_then_bb);
          // i의 값에 따라 bodyBB와 endBB로 분기하는 분기문 생성
          BasicBlock::iterator to_remove2 = if_then_bb->begin();
          Instruction* inst_to_remove2 = &(*to_remove2); 
          // inst_to_remove -> dropAllReferences();
          inst_to_remove2 -> eraseFromParent();

          BasicBlock *case_1_bb = splitBasicBlockByLinePoint(switch_bb,"case_1_bb",0);
          IRBuilder<> builder_switch(switch_bb);
          Value *var_switch = builder_switch.CreateLoad(var_i);
          BasicBlock::iterator to_remove3 = switch_bb->begin();
          Instruction* inst_to_remove3 = &(*to_remove3); 
          // inst_to_remove -> dropAllReferences();
          inst_to_remove3 -> eraseFromParent();

          BasicBlock *case_2_bb = splitBasicBlockByLinePoint(case_1_bb, "case_2_bb", 0);
          IRBuilder<> builder_case_1_bb(case_1_bb);

          BasicBlock *case_3_bb = splitBasicBlockByLinePoint(case_2_bb, "case_3_bb", 0);
          IRBuilder<> builder_case_2_bb(case_2_bb);
          

          // switch default 블럭 생성
          BasicBlock *sw_default_bb = BasicBlock::Create(f.getContext(), "sw_default_bb", &f, true_bb);
          IRBuilder<> builder_sw_default(sw_default_bb);
          builder_sw_default.CreateBr(if_then_bb);
          

          // // switch 문 생성
          SwitchInst *switch_inst = builder_switch.CreateSwitch(var_switch, sw_default_bb, bb.size());

          switch_inst->addCase(builder_switch.getInt32(0),case_1_bb);
          switch_inst->addCase(builder_switch.getInt32(1),case_2_bb);
          switch_inst->addCase(builder_switch.getInt32(2),case_3_bb);

        
          errs() << *entry_bb << "\n";
          errs() << *if_then_bb << "\n";
          errs() << *true_bb << "\n";
          errs() << *false_bb << "\n";
          errs() << *switch_bb << "\n";
          errs() << *case_1_bb << "\n";
          errs() << *case_2_bb << "\n";
          errs() << *case_3_bb << "\n";
          errs() << *sw_default_bb << "\n";

        }
      }
      return false;
    }
  };
}


char toCompare::ID = 0;
static RegisterPass<toCompare> X("to", "toCompare file",false, false);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM)
    { PM.add(new toCompare()); });
