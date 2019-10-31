#ifndef LIB_POSIX_IFINDEX_H_
#define LIB_POSIX_IFINDEX_H_

#include "lib/base/opaque_value.h"

namespace posix {

// Strongly typed POSIX ifindex wrapper.
DEFINE_OPAQUE_VALUE(int, IfIndex);

}  // namespace posix

#endif  // LIB_POSIX_IFINDEX_H_