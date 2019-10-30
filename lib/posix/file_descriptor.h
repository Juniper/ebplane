#ifndef LIB_POSIX_FILE_DESCRIPTOR_H_
#define LIB_POSIX_FILE_DESCRIPTOR_H_

#include "lib/base/opaque_value.h"

namespace posix {

// Strongly typed POSIX file descriptor wrapper.
//
// Example usage:
//
// FileDescriptor fd(open("/some/path", FLAGS));
// ...
// close(GetValue(fd));  // Wrapped value can be extracted.
//
DEFINE_OPAQUE_VALUE(int, FileDescriptor);

// Canonical value to represent an invalid file descriptor.
// Any negative value may be used but we prefer this one.
constexpr FileDescriptor kInvalidFileDescriptor(-1);

// Idiom to test for a valid looking file descriptor.
//
// No effort is made to check with the OS for a valid file descriptor. Any such
// attempt is futile as there is an unavoidable time-of-check-to-time-of-use
// race.
inline constexpr bool IsWellFormed(const FileDescriptor fd) {
  return 0 <= GetValue(fd);
}

}  // namespace posix

#endif  // LIB_POSIX_FILE_DESCRIPTOR_H_