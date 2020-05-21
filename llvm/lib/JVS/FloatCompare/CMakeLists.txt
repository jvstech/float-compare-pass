add_llvm_component_library(JVSFloatCompare
  FloatCompare.cpp
  
  ADDITIONAL_HEADER_DIRS
    ${LLVM_MAIN_INCLUDE_DIRS}/llvm/JVS
    
  DEPENDS
    intrinsics_gen
  )
