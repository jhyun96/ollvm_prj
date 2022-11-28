add_llvm_library(testFla MODULE
  CryptoUtils.cpp
  Utils.cpp
  testFla.cpp

  PLUGIN_TOOL
  opt
  )

# add_dependencies(LLVMObfuscation intrinsics_gen)
