#ifndef LIB_BASE_INVARIANT_H_
#define LIB_BASE_INVARIANT_H_

#include <cassert>

// The following macros exist to document preconditions and invariants that are
// not typically data dependent. A failure of an INVARIANT_* implies a logic
// error by the programmer that should be statically preventable but cannot be
// statically verified. A failure of INVARIANT_* is program fatal althrough
// invariant checking may not be enabled in all build targets.
//
// When possible, functions should handle errors and possibly notify the caller.
// Unfortunately certain simple functions need to make assumptions about their
// inputs and environment when returning an error is prohibitively complex or
// expensive.
//
// In exception-free C++ constructors and destructors are common contexts where
// invariants may exist but no path exists to return an error.
//
// Example code where INVARIANT_* is recommended:
//
// void Pop(Stack* stack) {
//     INVARIANT_F(IsEmpty(stack));  // Can't pop from empty stack.
//     ...
// }
//
// This code provides run-time feedback to programmers who write code like the
// following where it is not possible to statically check for preconditions:
//
// if (IsEmpty(stack)) {
//   Pop(stack);  // Obviously an error.
// }
//
// Note that the code passed to INVARIANT_* macros is not guaranteed to be
// executed in all build targets. Asserting invariants directly on impure
// functions is almost always an error.
//
// Don't do this:
// INVARIANT_T(FunctionWithSideEffects());
//
// Do this instead:
// const auto result = FunctionWithSideEffects();
// INVARIANT_T(result);
//
#define INVARIANT_T(pred) assert(pred)
#define INVARIANT_F(pred) INVARIANT_T(!(pred))
#define INVARIANT_EQ(a, b) INVARIANT_T((a) == (b))
#define INVARIANT_NE(a, b) INVARIANT_T((a) != (b))
#define INVARIANT_LT(a, b) INVARIANT_T((a) < (b))
#define INVARIANT_LE(a, b) INVARIANT_T((a) <= (b))
#define INVARIANT_GE(a, b) INVARIANT_T((a) >= (b))
#define INVARIANT_GT(a, b) INVARIANT_T((a) > (b))

#endif  // LIB_BASE_INVARIANT_H_