#if !defined(JVS_ANALYSIS_FLOATCOMPAREANALYSIS_H_)
#define JVS_ANALYSIS_FLOATCOMPAREANALYSIS_H_

#include <optional>
#include <vector>

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

// forward declarations
namespace llvm
{

class FCmpInst;
class Function;
class Module;
class raw_ostream;

} // namespace llvm

namespace jvs
{

class FloatComparisons
{
  llvm::Function* function_{nullptr};
  std::vector<llvm::FCmpInst*> comparisons_{};

public:
  FloatComparisons(llvm::Function& func,
    std::vector<llvm::FCmpInst*>&& fcmpInsts);

  llvm::Function* function() const;
  const std::vector<llvm::FCmpInst*>& comparisons() const;
  void Print(llvm::raw_ostream& os) const;
};

struct FloatCompareAnalysis : llvm::AnalysisInfoMixin<FloatCompareAnalysis>
{
  using Result = FloatComparisons;
  Result run(llvm::Function& func, llvm::FunctionAnalysisManager& manager);
  Result run(llvm::Function& func);

private:
  friend struct llvm::AnalysisInfoMixin<FloatCompareAnalysis>;
  static llvm::AnalysisKey Key;
};

class FloatCompareAnalysisPrinter
  : public llvm::PassInfoMixin<FloatCompareAnalysisPrinter>
{
  llvm::raw_ostream& os_;

public:
  explicit FloatCompareAnalysisPrinter(llvm::raw_ostream& os);
  llvm::PreservedAnalyses run(llvm::Function& func,
    llvm::FunctionAnalysisManager& manager);
};

} // namespace jvs

struct FloatCompareAnalysisWrapper : llvm::FunctionPass
{
  static char ID;
  FloatCompareAnalysisWrapper();

  const jvs::FloatComparisons& results() const;

  bool runOnFunction(llvm::Function& func) override;
  void getAnalysisUsage(llvm::AnalysisUsage& au) const override;
  void print(llvm::raw_ostream& os, const llvm::Module* m = nullptr) const
    override;

private:
  std::optional<jvs::FloatComparisons> results_{};
};


#endif // !JVS_ANALYSIS_FLOATCOMPAREANALYSIS_H_
