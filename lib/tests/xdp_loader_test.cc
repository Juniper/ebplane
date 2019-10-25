#include "gtest/gtest.h"
#include "lib/ebpf/sample.h"
#include "lib/xdp_loader.h"
#include <iostream>
#include <string_view>

using namespace std;

extern const char *argv[];

TEST(XdpLoader, Test1) {
  // File is in ELF, we cannot really check it. Verify at least it is ELF.
  EXPECT_EQ(0, ebpf::sample.find("\x7f""ELF", 0));
  cout << "ebpf sample size " << ebpf::sample.size() << "\n";
  XdpHandle xdph = LoadXdpBuffer(ebpf::sample, "ebpf_sample");
  EXPECT_EQ(1, (xdph != nullptr));
}

