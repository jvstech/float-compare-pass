#include "llvm/Analysis/JVS/FloatCompareAnalysis.h"

#include <cassert>
#include <utility>

#include "llvm/Analysis/Passes.h"
#include "llvm/InitializePasses.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ModuleSlotTracker.h"
#include "llvm/JVS/FloatCompare.h"
#include "llvm/PassRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

namespace jvs
{

static constexpr char PassName[] = "jvs-fcmp-eq-analysis";
static constexpr char PassDescription[] =
  "Find floating-point equality comparisons";

} // namespace jvs

#define DEBUG_TYPE ::jvs::PassName

jvs::FloatComparisons::FloatComparisons(llvm::Function& func,
  std::vector<llvm::FCmpInst*>&& fcmpInsts)
  : function_(&func),
  comparisons_(std::move(fcmpInsts))
{
}

llvm::Function* jvs::FloatComparisons::function() const
{
  return function_;
}

const std::vector<llvm::FCmpInst*>& jvs::FloatComparisons::comparisons() const
{
  return comparisons_;
}

void jvs::FloatComparisons::Print(llvm::raw_ostream& os) const
{
  if (!comparisons_.empty())
  {
    // Using a ModuleSlotTracker for printing makes it so full function
    // analysis for slot numbering only occurs once instead of every time an
    // instruction is printed.
    llvm::ModuleSlotTracker slotTracker{function_->getParent()};
    os << "Floating-point equality comparisons in \"" << function_->getName()
      << "\":\n";
    for (llvm::FCmpInst* fcmpInst : comparisons_)
    {
      fcmpInst->print(os, slotTracker);
      os << '\n';
    }
  }
}

jvs::FloatCompareAnalysis::Result jvs::FloatCompareAnalysis::run(
  llvm::Function& func, llvm::FunctionAnalysisManager& manager)
{
  return run(func);
}

jvs::FloatCompareAnalysis::Result jvs::FloatCompareAnalysis::run(
  llvm::Function& func)
{
  std::vector<llvm::FCmpInst*> comparisons = jvs::FindFPEQComparisons(func);
  FloatComparisons result{func, std::move(comparisons)};
  return result;
}

llvm::AnalysisKey jvs::FloatCompareAnalysis::Key{};

jvs::FloatCompareAnalysisPrinter::FloatCompareAnalysisPrinter(
  llvm::raw_ostream& os)
  : os_(os)
{
}

llvm::PreservedAnalyses jvs::FloatCompareAnalysisPrinter::run(
  llvm::Function& func, llvm::FunctionAnalysisManager& manager)
{
  auto& floatComparisons = manager.getResult<FloatCompareAnalysis>(func);
  floatComparisons.Print(os_);
  return llvm::PreservedAnalyses::all();
}

FloatCompareAnalysisWrapper::FloatCompareAnalysisWrapper()
  : llvm::FunctionPass(ID)
{
  llvm::initializeFloatCompareAnalysisWrapperPass(
    *llvm::PassRegistry::getPassRegistry());
}

const jvs::FloatComparisons& FloatCompareAnalysisWrapper::results() const
{
  assert(results_ &&
    "Floating-point comparison analysis has not been performed yet.");
  return *results_;
}

bool FloatCompareAnalysisWrapper::runOnFunction(llvm::Function& func)
{
  jvs::FloatCompareAnalysis analysis{};
  results_ = analysis.run(func);
  return false;
}

void FloatCompareAnalysisWrapper::getAnalysisUsage(llvm::AnalysisUsage& au)
  const
{
  au.setPreservesAll();
}

void FloatCompareAnalysisWrapper::print(llvm::raw_ostream& os,
  const llvm::Module* m) const
{
  if (!results_)
  {
    os << "Floating-point comparison analysis has not been performed yet.\n";
    return;
  }

  results_->Print(os);
}

char FloatCompareAnalysisWrapper::ID = 0;

using namespace llvm;

INITIALIZE_PASS(FloatCompareAnalysisWrapper, jvs::PassName,
  jvs::PassDescription, false, true)

llvm::FunctionPass* llvm::createFloatCompareAnalysisWrapperPass()
{
  return new FloatCompareAnalysisWrapper();
}
