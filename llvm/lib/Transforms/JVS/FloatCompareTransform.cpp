#include "llvm/Transforms/JVS/FloatCompareTransform.h"

#include <cassert>

#include "llvm/ADT/Statistic.h"
#include "llvm/InitializePasses.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/JVS/FloatCompare.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/IPO.h"

namespace jvs
{

static constexpr char PassName[] = "jvs-fcmp-eq-transform";
static constexpr char PassDescription[] = "Convert FP equality comparisons";

} // namespace jvs

#define DEBUG_TYPE ::jvs::PassName
STATISTIC(FCmpEqConversionCount,
  "Number of direct FP equality comparisons converted");

llvm::PreservedAnalyses jvs::FloatCompareTransform::run(
  llvm::Function& func, llvm::FunctionAnalysisManager& manager)
{
  auto& floatComparisons = manager.getResult<FloatCompareAnalysis>(func);
  bool modified = run(floatComparisons);
  return modified
    ? llvm::PreservedAnalyses::all()
    : llvm::PreservedAnalyses::none();
}

bool jvs::FloatCompareTransform::run(
  const jvs::FloatComparisons& floatComparisons)
{
  bool modified{false};
  // Functions marked explicitly 'optnone' should be ignored since we shouldn't
  // be changing anything in them anyway.
  if (floatComparisons.function()->hasFnAttribute(
    llvm::Attribute::OptimizeNone))
  {
    LLVM_DEBUG(llvm::dbgs() << "Ignoring optnone-marked function \""
      << floatComparisons.function()->getName() << "\"\n");
    return modified;
  }

  for (llvm::FCmpInst* fcmpInst : floatComparisons.comparisons())
  {
    if (jvs::ConvertFPEQComparison(fcmpInst))
    {
      ++FCmpEqConversionCount;
      modified = true;
    }
  }

  return modified;
}

FloatCompareTransformWrapper::FloatCompareTransformWrapper()
  : llvm::FunctionPass(ID)
{
  llvm::initializeFloatCompareTransformWrapperPass(
    *llvm::PassRegistry::getPassRegistry());
}

void FloatCompareTransformWrapper::getAnalysisUsage(llvm::AnalysisUsage& au)
  const
{
  // This transform does not modify the control flow graph, so we mark it as
  // preserved here.
  au.setPreservesCFG();
  // Since we're using the results of FloatCompareAnalysisWrapper, we add it
  // as a required analysis pass here.
  au.addRequired<FloatCompareAnalysisWrapper>();
}

bool FloatCompareTransformWrapper::runOnFunction(llvm::Function& func)
{
  auto& analysis = getAnalysis<FloatCompareAnalysisWrapper>();
  jvs::FloatCompareTransform transform{};
  bool modified = transform.run(analysis.results());
  return modified;
}

char FloatCompareTransformWrapper::ID = 0;

using namespace llvm;

INITIALIZE_PASS_BEGIN(FloatCompareTransformWrapper, jvs::PassName,
  jvs::PassDescription, false, false)
INITIALIZE_PASS_DEPENDENCY(FloatCompareAnalysisWrapper)
INITIALIZE_PASS_END(FloatCompareTransformWrapper, jvs::PassName,
  jvs::PassDescription, false, false)

llvm::FunctionPass* llvm::createFloatCompareTransformWrapperPass()
{
  return new FloatCompareTransformWrapper();
}
