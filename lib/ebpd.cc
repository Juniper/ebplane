#include "lib/ebpd.h"
#include "lib/ebpf/sample.h"

#include <iostream>

// This is just an example function.
// The ebpf code is available as std::string_view named embedded::sample_pic_o.
// embedded::sample_pic_o.data() and embedded::sample_pic_o.size() provide
// access to the bytecode.
void func(void) {
  std::cout << embedded::sample_pic_o.size() << std::endl;
}
