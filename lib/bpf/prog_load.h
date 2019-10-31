#ifndef LIB_BPF_PROG_LOAD_H_
#define LIB_BPF_PROG_LOAD_H_

#include <cstring>
#include <string>
#include <string_view>

#include "lib/bpf/bpf.h"
#include "lib/error/assign_or_return.h"
#include "lib/error/status_or.h"
#include "lib/posix/ifindex.h"
#include "lib/posix/unique_file_descriptor.h"

namespace bpf {

// BPF_PROG_LOAD wrapper.
//
// TODO: Incomplete.
//
// See 'man 2 bpf' for details.
inline error::StatusOr<posix::UniqueFileDescriptor> ProgLoad(
    const uint32_t program_type, std::string_view instructions,
    const std::string& license, const uint32_t program_flags,
    const std::string& name, const posix::IfIndex ifindex) {
  constexpr size_t kInstructionSize = 8;
  bpf_attr attr = {};
  attr.prog_type = program_type;
  attr.insn_cnt = instructions.size() / kInstructionSize;
  attr.insns = reinterpret_cast<uintptr_t>(instructions.data());
  attr.license = reinterpret_cast<uintptr_t>(license.c_str());
  // TODO: Log buffer? Need std::span<char> equivalent.
  // TODO: Kernel version? Only needed for perf programs?.
  attr.prog_flags = program_flags;
  strncpy(attr.prog_name, name.c_str(), sizeof(attr.prog_name));
  attr.prog_ifindex = GetValue(ifindex);
  ASSIGN_OR_RETURN(const auto fd, Bpf(BPF_PROG_LOAD, &attr));
  return posix::MakeUniqueFileDescriptor(fd);
}

}  // namespace bpf

#endif  // LIB_BPF_PROG_LOAD_H_