add_llvm_component_library(JVSAnalysis
  FloatCompareAnalysis.cpp
  
  ADDITIONAL_HEADER_DIRS
    ${LLVM_MAIN_INCLUDE_DIR}/llvm/JVS
    ${LLVM_MAIN_INCLUDE_DIR}/llvm/Analysis
    ${LLVM_MAIN_INCLUDE_DIR}/llvm/Analysis/JVS
    
  LINK_LIBS
    JVSFloatCompare
    
  DEPENDS
    intrinsics_gen
  )

set_target_properties(JVSAnalysis
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
  )
