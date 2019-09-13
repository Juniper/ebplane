#include "gtest/gtest.h"
#include "build/tests/dependency.h"

#include <string_view>

TEST(EmbedTest, SimpleTest) {
  // Exact content of the file cannot be easily checked, would need an arch
  // arch format parser. Just the fact it is an arch file with the  desired
  // name is a strong indication that the process worked.
  EXPECT_EQ(0, embedded::mediocrity_a.find("!<arch>", 0));
  EXPECT_EQ(0, embedded::perseverance_a.find("!<arch>", 0));
}
