#ifndef LIB_BPF_MAP_LOOKUP_ELEMENT_H_
#define LIB_BPF_MAP_LOOKUP_ELEMENT_H_

#include "lib/bpf/bpf.h"
#include "lib/error/return_if_error.h"
#include "lib/error/status_or.h"
#include "lib/posix/file_descriptor.h"

namespace bpf {

// BPF_MAP_LOOKUP_ELEM wrapper.
// Lookup an element identified by 'key' in the map identified by 'fd'.
// The types of KeyT and ValueT must match those provided to MapCreate() when
// 'fd' was created.
//
// Return the stored value on success or an error status on lookup failure.
//
// See 'man 2 bpf' for details.
template <typename KeyT, typename ValueT>
inline error::StatusOr<ValueT> MapLookupElement(const posix::FileDescriptor fd,
                                                const KeyT& key) {
  ValueT value = {};
  bpf_attr attr = {};
  attr.map_fd = GetValue(fd);
  attr.key = reinterpret_cast<uintptr_t>(&key);
  attr.value = reinterpret_cast<uintptr_t>(&value);
  RETURN_IF_ERROR(GetStatus(Bpf(BPF_MAP_LOOKUP_ELEM, &attr)));
  return value;
}

}  // namespace bpf

#endif  // LIB_BPF_MAP_LOOKUP_ELEMENT_H_