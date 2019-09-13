#include "lib/ebpd.h"
#include "lib/ebpf/sample.h"

#include <iostream>

// This is just an example function.
// The ebpf code is available as std::string_view named ebpf::sample.
// ebpf::sample.data() and ebpf::sample.size() provide access to the bytecode.
void func(void) {
  std::cout << ebpf::sample.size() << std::endl;
}
