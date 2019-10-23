#ifndef LIB_ERROR_STATUS_OR_H_
#define LIB_ERROR_STATUS_OR_H_

#include <variant>

#include "lib/base/invariant.h"
#include "lib/error/status.h"

namespace error {
namespace impl {

// Index of Value and Status in StatusOr variant.
constexpr int kStatusOrValueIdx = 0;
constexpr int kStatusOrStatusIdx = 1;

}  // namespace impl

// Type describing the result of an operation that may encounter an error but
// returns some type on success. As StatusOr is based on Status, this
// implementation assumes that errors are rare and optimizes accordingly.
//
// The following helpers exist to check for common conditions:
// IsOk() and IsError().
//
// Specific status or value contents may be accessed using:
// GetStatus() and GetValue().
//
// Example usage:
//
// StatusOr<std::unique_ptr<int>> Foo(int bar) {
//     if (bar > 0) {
//       return bar;
//     }
//     return Status(Code::INVALID_ARGUMENT, "negative bar encountered");
// }
//
// auto status_or = Foo(-1);
// if (IsOk(status_or)) {
//   std::cout << *std::move(GetValue(status_or)) << "\n";
// } else {
//   std::cout << "Error! " << GetText(GetStatus(status_or)) << "\n";
// }
//
template <typename T>
using StatusOr = std::variant<T, Status>;

// Idiom to check for OK result.
// Return true iff code == Code::OK.
template <typename T>
inline bool IsOk(const StatusOr<T>& status_or) {
  return impl::kStatusOrValueIdx == status_or.index();
}

// Idiom to check for error result.
// Return true iff code != Code::OK.
template <typename T>
inline bool IsError(const StatusOr<T>& status_or) {
  return !IsOk(status_or);
}

// Return status of 'status_or'.
template <typename T>
inline Status GetStatus(const StatusOr<T>& status_or) {
  return IsOk(status_or) ? kOkStatus
                         : std::get<impl::kStatusOrStatusIdx>(status_or);
}

// Return value of 'status_or'.
// Requires that IsOk(status_or) == true.
template <typename T>
inline T& GetValue(StatusOr<T>& status_or) {
  INVARIANT_T(IsOk(status_or));
  return std::get<impl::kStatusOrValueIdx>(status_or);
}

// Return value of 'status_or'.
// Requires that IsOk(status_or) == true.
template <typename T>
inline T&& GetValue(StatusOr<T>&& status_or) {
  INVARIANT_T(IsOk(status_or));
  return std::get<impl::kStatusOrValueIdx>(std::move(status_or));
}

// Return value of 'status_or'.
// Requires that IsOk(status_or) == true.
template <typename T>
inline const T& GetValue(const StatusOr<T>& status_or) {
  INVARIANT_T(IsOk(status_or));
  return std::get<impl::kStatusOrValueIdx>(status_or);
}

// Return value of 'status_or'.
// Requires that IsOk(status_or) == true.
template <typename T>
inline const T&& GetValue(const StatusOr<T>&& status_or) {
  INVARIANT_T(IsOk(status_or));
  return std::get<impl::kStatusOrValueIdx>(std::move(status_or));
}

}  // namespace error

#endif  // LIB_ERROR_STATUS_OR_H_