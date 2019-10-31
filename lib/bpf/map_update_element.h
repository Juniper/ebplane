#ifndef LIB_BPF_MAP_UPDATE_ELEMENT_H_
#define LIB_BPF_MAP_UPDATE_ELEMENT_H_

#include "lib/bpf/bpf.h"
#include "lib/error/return_if_error.h"
#include "lib/error/status.h"
#include "lib/posix/file_descriptor.h"

namespace bpf {

// BPF_MAP_UPDATE_ELEM wrapper.
// Insert or update an element identified by 'key' to hold 'value' in the map
// identified by 'fd'. The types of KeyT and ValueT must match those provided
// to MapCreate() when 'fd' was created.
//
// Return kOkStatus on success or an error status on failure.
//
// See 'man 2 bpf' for details.
template <typename KeyT, typename ValueT>
inline error::Status MapUpdateElement(const posix::FileDescriptor fd,
                                      const KeyT& key, const ValueT& value) {
  bpf_attr attr = {};
  attr.map_fd = GetValue(fd);
  attr.key = reinterpret_cast<uintptr_t>(&key);
  attr.value = reinterpret_cast<uintptr_t>(&value);
  return GetStatus(Bpf(BPF_MAP_UPDATE_ELEM, &attr));
}

}  // namespace bpf

#endif  // LIB_BPF_MAP_UPDATE_ELEMENT_H_