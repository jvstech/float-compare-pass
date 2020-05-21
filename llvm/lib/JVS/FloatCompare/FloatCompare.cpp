#include "llvm/JVS/FloatCompare.h"

#include <cassert>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/ErrorHandling.h"

std::vector<llvm::FCmpInst*> jvs::FindFPEQComparisons(llvm::Function& func)
{
  std::vector<llvm::FCmpInst*> foundInsts{};
  for (llvm::BasicBlock& block : func)
  {
    for (llvm::Instruction& inst : block)
    {
      // We're only looking for 'fcmp' instructions.
      if (auto* fcmpInst = llvm::dyn_cast<llvm::FCmpInst>(&inst))
      {
        // We're only looking for 'fcmp oeq/ueq/one/une' instructions.
        if (fcmpInst->isEquality())
        {
          foundInsts.push_back(fcmpInst);
        }
      }
    }
  }

  return foundInsts;
}

llvm::FCmpInst* jvs::ConvertFPEQComparison(llvm::FCmpInst* fcmpInst)
{
  assert(fcmpInst && "fcmp instruction is null.");

  if (!fcmpInst->isEquality())
  {
    // We're only interested in equality-based comparisons, so return a null if
    // this comparison isn't equality-based.
    return nullptr;
  }

  llvm::Value* lhsOperand = fcmpInst->getOperand(0);
  llvm::Value* rhsOperand = fcmpInst->getOperand(1);
  // Determine the new floating-point comparison predicate based on the current
  // one.
  llvm::CmpInst::Predicate cmpPred = [fcmpInst]()
  {
    switch (fcmpInst->getPredicate())
    {
    case llvm::CmpInst::Predicate::FCMP_OEQ:
      return llvm::CmpInst::Predicate::FCMP_OLT;
    case llvm::CmpInst::Predicate::FCMP_UEQ:
      return llvm::CmpInst::Predicate::FCMP_ULT;
    case llvm::CmpInst::Predicate::FCMP_ONE:
      return llvm::CmpInst::Predicate::FCMP_OGE;
    case llvm::CmpInst::Predicate::FCMP_UNE:
      return llvm::CmpInst::Predicate::FCMP_UGE;
    default:
      llvm_unreachable("Unsupported fcmp predicate.");
    }
  }();

  // Create the objects and values needed to perform the equality comparison
  // conversion.
  llvm::Module* m = fcmpInst->getModule();
  assert(m && "fcmp instruction does not belong to a module.");
  llvm::LLVMContext& ctx = m->getContext();
  llvm::IntegerType* i64Type = llvm::IntegerType::get(ctx, 64);
  llvm::Type* doubleType = llvm::Type::getDoubleTy(ctx);

  // Define the sign-mask and double-precision machine epsilon constants.
  llvm::ConstantInt* signMask = llvm::ConstantInt::get(i64Type, ~(1L << 63));
  // The machine epsilon value for IEEE 754 double-precision values is 2 ^ -52
  // or (b / 2) * b ^ -(p - 1) where b (base) = 2 and p (precision) = 53.
  llvm::APInt epsilonBits{64, 0x3CB0000000000000};
  llvm::Constant* epsilonValue =
    llvm::ConstantFP::get(doubleType, epsilonBits.bitsToDouble());

  // Create an IRBuilder with an insertion point set to the given fcmp
  // instruction.
  llvm::IRBuilder<> builder{fcmpInst};
  // Create the subtraction, casting, absolute value, and new comparison
  // instructions one at a time.

  // %0 = fsub double %a, %b
  auto* fsubInst = builder.CreateFSub(lhsOperand, rhsOperand);
  // %1 = bitcast double %0 to i64
  auto* castToI64 = builder.CreateBitCast(fsubInst, i64Type);
  // %2 = and i64 %1, 0x7fffffffffffffff
  auto* absValue = builder.CreateAnd(castToI64, signMask);
  // %3 = bitcast i64 %2 to double
  auto* castToDouble = builder.CreateBitCast(absValue, doubleType);
  // %4 = fcmp <olt/ult/oge/uge> double %3, 0x3cb0000000000000
  // Rather than creating a new instruction, we'll just change the predicate and
  // operands of the existing fcmp instruction to match what we want.
  fcmpInst->setPredicate(cmpPred);
  fcmpInst->setOperand(0, castToDouble);
  fcmpInst->setOperand(1, epsilonValue);
  return fcmpInst;
}
