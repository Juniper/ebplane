#include "lib/posix/errno.h"

#include <cerrno>

namespace posix {

error::Code CaptureErrnoAsCode() { return MakeCodeFromErrno(errno); }

}  // namespace posix
