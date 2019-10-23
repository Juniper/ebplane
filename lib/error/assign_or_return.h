#ifndef LIB_ERROR_ASSIGN_OR_RETURN_H_
#define LIB_ERROR_ASSIGN_OR_RETURN_H_

#include "lib/error/return_if_error.h"

// Macro to evaluate an expression and immediately return an error status if the
// expression returned an error. On success the result of GetValue('expr') will
// be assigned to 'lvalue'. ASSIGN_OR_RETURN() will work with any expression
// that returns a type implementing an overload of IsError(GetStatus()) and
// GetValue().
//
// IsError(GetStatus()) and GetValue() must be in the invoking namespace or
// discoverable using ADL.
//
// ASSIGN_OR_RETURN() achieves a similar result to the 'do' syntax in Haskell
// and other functional languages. The return type of 'expr' in ASSIGN_OR_RETURN
// is very similar to the Maybe monad in Haskell.
//
// The most direct example of ASSIGN_OR_RETURN() in other contexts is the rust
// try! macro which combines the functionality of RETURN_IF_ERROR() and
// ASSIGN_OR_RETURN().
//
// Example usage:
//
// StatusOr<int> Foo() {...}
// StatusOr<int> Bar() {...}
// StatusOr<int> Baz() {...}
//
// StatusOr<int> MyCompositionalFunction() {
//   ASSIGN_OR_RETURN(const auto a, Foo());
//   ASSIGN_OR_RETURN(const auto b, Bar());
//   ASSIGN_OR_RETURN(const auto c, Baz());
//   return a + b + c;
// }
//
// ASSIGN_OR_RETURN() can also assign to explicitly defined variables, members
// as well as overwrite existing values.
//
// StatusOr<int> MyCompositionalFunction() {
//   int a = 0;
//   ASSIGN_OR_RETURN(a, Foo());  // Overwrite 'a' or any other lvalue.
//   ASSIGN_OR_RETURN(const int b, Bar());  // Force 'b' to be an int.
//   ASSIGN_OR_RETURN(const auto c, Baz());  // 'c' is the return type of
//   GetValue(). return a + b + c;
// }
//
// Compare to the same function without the ASSIGN_OR_RETURN() macro:
//
// StatusOr<int> MyCompositionalFunction() {
//   int a = 0;
//   int b = 0;
//   int c = 0;
//   {
//     const auto result = Foo();
//     const auto status = GetStatus(result);
//     if (IsError(status)) {
//       return status;
//     }
//     a = GetValue(result);
//   }
//   {
//     const auto result = Bar();
//     const auto status = GetStatus(result);
//     if (IsError(status)) {
//       return status;
//     }
//     b = GetValue(result);
//   }
//   {
//     const auto result = Baz();
//     const auto status = GetStatus(result);
//     if (IsError(status)) {
//       return status;
//     }
//     c = GetValue(result);
//   }
//   return a + b + c;
// }
//
#define ASSIGN_OR_RETURN(lvalue, expr)           \
  lvalue = ({                                    \
    auto _try_assign_tmp = (expr);               \
    RETURN_IF_ERROR(GetStatus(_try_assign_tmp)); \
    GetValue(std::move(_try_assign_tmp));        \
  })

#endif  // LIB_ERROR_ASSIGN_OR_RETURN_H_