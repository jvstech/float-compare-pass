#if !defined(JVS_FLOATCOMPARE_H_)
#define JVS_FLOATCOMPARE_H_

#include <vector>

// forward declarations
namespace llvm
{

class FCmpInst;
class Function;

} // namespace llvm

namespace jvs
{

std::vector<llvm::FCmpInst*> FindFPEQComparisons(llvm::Function& func);
llvm::FCmpInst* ConvertFPEQComparison(llvm::FCmpInst* fcmpInst);

} // namespace jvs


#endif // !JVS_FLOATCOMPARE_H_
