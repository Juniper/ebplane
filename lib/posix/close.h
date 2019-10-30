#ifndef LIB_POSIX_CLOSE_H_
#define LIB_POSIX_CLOSE_H_

#include <errno.h>
#include <unistd.h>

#include "lib/error/status.h"
#include "lib/posix/errno.h"
#include "lib/posix/file_descriptor.h"

namespace posix {

inline ::error::Status Close(const FileDescriptor fd) {
  const auto rv = ::close(GetValue(fd));
  return OkStatusOrCaptureErrnoIf(-1 == rv, "close() failed");
}

}  // namespace posix

#endif  // LIB_POSIX_CLOSE_H_