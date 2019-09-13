#include "gtest/gtest.h"
#include "build/tests/ebpf_sample.h"

#include <string_view>

TEST(EmbedTest, SimpleTest) {
  // File is in ELF, we cannot really check it. Verify at least it is ELF.
  EXPECT_EQ(0, embedded::ebpf_sample_pic_o.find("\x7f""ELF", 0));
}
