add_llvm_library( LLVMMyFlattening MODULE
  MyFlattening.cpp

  PLUGIN_TOOL
  opt
  )