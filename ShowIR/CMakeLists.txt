add_llvm_library( LLVMShowIR MODULE
  ShowIR.cpp

  PLUGIN_TOOL
  opt
  )