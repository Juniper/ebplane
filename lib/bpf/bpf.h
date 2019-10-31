#ifndef LIB_BPF_BPF_H_
#define LIB_BPF_BPF_H_

#include <sys/syscall.h>

#include "lib/error/status_or.h"
#include "lib/posix/syscall.h"

namespace bpf {

// bpf() syscall wrapper. No C standard library support currently exists.
//
// See "man 2 bpf" for details.
inline error::StatusOr<int> Bpf(const int cmd, bpf_attr* const attr) {
  return posix::Syscall(__NR_bpf, cmd, attr, sizeof(*attr));
}

}  // namespace bpf

#endif  // LIB_BPF_BPF_H_