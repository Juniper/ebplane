#ifndef LIB_ERROR_ERRNO_H_
#define LIB_ERROR_ERRNO_H_

#include "lib/error/code.h"
#include "lib/error/status.h"

namespace error {

// Convert a numeric constant from the system errno.h and friends into a Code.
inline Code MakeCodeFromErrno(const int e) {
  return std::system_error(e, std::generic_category()).code();
}

// Idiom to capture 'errno' and construct a Code using that value.
//
// CaptureErrnoAsCode() is definied in errno.cc to keep the 'errno' macro out of
// header files whenever possible.
Code CaptureErrnoAsCode();

// Idiom to capture 'errno' and construct a Status using that value and 'text'.
inline Status CaptureErrnoAsStatus(const std::string_view text) {
  return Status(CaptureErrnoAsCode(), text);
}

// Idiom to capture 'errno' and construct a Status using that value and 'text'
// if 'predicate' is true, return kOkStatus otherwise.
//
// Example usage:
//
// Status Close(const posix::file_descriptor fd) {
//   const auto rv = ::close(GetValue(fd));
//   return OkStatusOrCaptureErrnoIf(0 != rv, "close() failed");
// }
//
inline Status OkStatusOrCaptureErrnoIf(const bool predicate,
                                       const std::string_view text) {
  return predicate ? CaptureErrnoAsStatus(text) : kOkStatus;
}

}  // namespace error

#endif  // LIB_ERROR_ERRNO_H_