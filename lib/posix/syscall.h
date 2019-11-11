#ifndef LIB_POSIX_SYSCALL_H_
#define LIB_POSIX_SYSCALL_H_

#include <unistd.h>

#include "lib/error/return_if_error.h"
#include "lib/error/status_or.h"
#include "lib/posix/errno.h"

namespace posix {

// Trivial syscall wrapper. Checks for error conditions and converts errno to
// error::Status.
//
// Return the result of syscall() on success or an error status on failure.
//
// Users should be aware that there is not a strict standard for syscall()
// return values. Always verify that '-1' is the preferred error representation
// before using this wrapper for a specific syscall.
//
// See 'man 2 syscall' for details.
template <typename... ArgsT>
inline error::StatusOr<int> Syscall(const int number, ArgsT&&... args) {
  const auto rv = ::syscall(number, std::forward<ArgsT>(args)...);
  RETURN_IF_ERROR(OkStatusOrCaptureErrnoIf(-1 == rv, "syscall() failed"));
  return rv;
}

}  // namespace posix

#endif  // LIB_POSIX_SYSCALL_H_