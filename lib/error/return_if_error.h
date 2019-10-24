#ifndef LIB_ERROR_RETURN_IF_ERROR_H_
#define LIB_ERROR_RETURN_IF_ERROR_H_

// Macro to evaluate an expression and immediately return an error status if
// the expression returned an error. RETURN_IF_ERROR() will work with any
// function that returns a type implementing an overload of IsError().
//
// IsError() must be in the invoking namespace or discoverable using ADL.
//
// Example usage:
//
// Status Foo() {...}
// Status Bar() {...}
// Status Baz() {...}
//
// Status MyCompositionalFunction() {
//   RETURN_IF_ERROR(Foo());
//   RETURN_IF_ERROR(Bar());
//   RETURN_IF_ERROR(Baz());
//   return ::error::kOkStatus;
// }
//
// Compare to the same function without the RETURN_IF_ERROR() macro:
//
// Status MyCompositionalFunction() {
//   {
//     const auto status = Foo();
//     if (IsError(status)) {
//       return status;
//     }
//   }
//   {
//     const auto status = Bar();
//     if (IsError(status)) {
//       return status;
//     }
//   }
//   {
//     const auto status = Baz();
//     if (IsError(status)) {
//       return status;
//     }
//   }
//   return ::error::kOkStatus;
// }
//
#define RETURN_IF_ERROR(expr)      \
  do {                             \
    const auto& _try_tmp = (expr); \
    if (IsError(_try_tmp)) {       \
      return _try_tmp;             \
    }                              \
  } while (false)

#endif  // LIB_ERROR_RETURN_IF_ERROR_H_