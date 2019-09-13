#include "gtest/gtest.h"
#include "build/tests/embed_test.h"
#include "build/tests/mediocrity.h"

#include <string_view>

TEST(EmbedTest, SimpleTest) {
  EXPECT_EQ(std::string(std::string_view(mediocrity, std::size(mediocrity) - 1)), embedded::mediocrity_txt);
}
