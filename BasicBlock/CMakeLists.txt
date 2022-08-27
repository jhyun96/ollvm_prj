add_llvm_library( LLVMBasicBlock MODULE 
  basic_pass.cpp

  PLUGIN_TOOL
  opt
  )