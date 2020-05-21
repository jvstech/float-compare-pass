#if !defined(JVS_TRANSFORM_FLOATCOMPARETRANSFORM_H_)
#define JVS_TRANSFORM_FLOATCOMPARETRANSFORM_H_

#include "llvm/Analysis/JVS/FloatCompareAnalysis.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

// forward declarations
namespace llvm
{

class Function;

} // namespace llvm

namespace jvs
{

struct FloatCompareTransform : llvm::PassInfoMixin<FloatCompareTransform>
{
  llvm::PreservedAnalyses run(llvm::Function& func,
    llvm::FunctionAnalysisManager& manager);
  bool run(const jvs::FloatComparisons& floatComparisons);
};

} // namespace jvs

struct FloatCompareTransformWrapper : llvm::FunctionPass
{
  static char ID;
  FloatCompareTransformWrapper();

  bool runOnFunction(llvm::Function& func) override;
  void getAnalysisUsage(llvm::AnalysisUsage& au) const override;
};


#endif // !JVS_TRANSFORM_FLOATCOMPARETRANSFORM_H_
