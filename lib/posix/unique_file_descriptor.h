#ifndef LIB_POSIX_UNIQUE_FILE_DESCRIPTOR_H_
#define LIB_POSIX_UNIQUE_FILE_DESCRIPTOR_H_

#include "lib/base/ignore.h"
#include "lib/base/invariant.h"
#include "lib/base/unique_value.h"
#include "lib/posix/close.h"
#include "lib/posix/file_descriptor.h"

namespace posix {
namespace impl {

struct UniqueFileDescriptorDtor {
  void operator()(const FileDescriptor fd) {
    INVARIANT_T(IsWellFormed(fd));
    base::Ignore(Close(fd));  // Nothing we can do about an error here.
  }
};

}  // namespace impl

// Type implementing a movable, automatically closing file descriptor. Use
// UniqueFileDescriptor to represent owned FileDescriptors.
//
// UniqueFileDescriptor must never contain a malformed FileDescriptor and will
// assert if one is present on destruction.
//
// A helper GetValue() is provided to access the wrapped value.
// operator* is provided to access the wrapped value.
// operator bool is provided to check for a wrapped value.
//
// See lib/base/unique_value.h for more implementation details.
//
// Example usage:
// {
//     UniqueFileDescriptor fd(open("/some/path", FLAGS));  // Ignoring errors.
//     DoSomethingWithFd(GetValue(fd));  // Free function style value access.
//     DoSomethingElseWithFd(*fd);  // std::unique_ptr style value access.
// }  // 'fd' leaves scope and is automatically closed!
//
using UniqueFileDescriptor =
    base::UniqueValue<FileDescriptor, impl::UniqueFileDescriptorDtor>;

}  // namespace posix

#endif  // LIB_POSIX_UNIQUE_FILE_DESCRIPTOR_H_