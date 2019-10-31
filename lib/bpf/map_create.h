#ifndef LIB_BPF_MAP_CREATE_H_
#define LIB_BPF_MAP_CREATE_H_

#include <cstring>
#include <string>
#include <string_view>

#include "lib/bpf/bpf.h"
#include "lib/error/assign_or_return.h"
#include "lib/error/status_or.h"
#include "lib/posix/unique_file_descriptor.h"

namespace bpf {

// BPF_MAP_CREATE wrapper.
// Create a map of 'map_type' from keys of type KeyT to values of type ValueT
// and maximum capacity of 'max_entries'.
//
// Return an owned file descriptor on success or an error status on failure.
//
// See 'man 2 bpf' for details.
template <typename KeyT, typename ValueT>
inline error::StatusOr<posix::UniqueFileDescriptor> MapCreate(
    const uint32_t map_type, const size_t max_entries) {
  bpf_attr attr = {};
  attr.map_type = map_type;
  attr.key_size = sizeof(KeyT);
  attr.value_size = sizeof(ValueT);
  attr.max_entries = max_entries;
  ASSIGN_OR_RETURN(const auto fd, Bpf(BPF_MAP_CREATE, &attr));
  return posix::MakeUniqueFileDescriptor(fd);
}

}  // namespace bpf

#endif  // LIB_BPF_MAP_CREATE_H_