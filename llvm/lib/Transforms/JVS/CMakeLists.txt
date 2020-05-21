add_llvm_component_library(JVSTransform
  FloatCompareTransform.cpp
  
  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms/JVS
  
  LINK_LIBS
    JVSAnalysis
    
  DEPENDS
    intrinsics_gen
  )
