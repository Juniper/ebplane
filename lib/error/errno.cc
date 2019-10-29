#include "lib/error/errno.h"

#include <cerrno>

namespace error {

Code CaptureErrnoAsCode() { return MakeCodeFromErrno(errno); }

}  // namespace error
