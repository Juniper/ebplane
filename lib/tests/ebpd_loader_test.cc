#include "gtest/gtest.h"
#include "lib/tests/ebpf_sample.h"
#include "lib/ebpd_loader.h"
#include <iostream>
#include <string_view>

using namespace std;

TEST(EbpdLoader, Test1) {
  // File is in ELF, we cannot really check it. Verify at least it is ELF.
  EXPECT_EQ(0, ebpf::ebpf_sample.find("\x7f""ELF", 0));
  cout << "ebpf sample size " << ebpf::ebpf_sample.size() << "\n";
  EbpdLoader *loader = new EbpdLoader();
  EXPECT_EQ(0, loader->LoadBuffer((void *)&ebpf::ebpf_sample[0],
                                  ebpf::ebpf_sample.size(), "ebpf_sample"));
}
