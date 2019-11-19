#include <array>
#include <vector>

#include "gtest/gtest.h"
#include "lib/base/span.h"

using namespace base;

TEST(OpaqueValueTest, NotNullable) {
  int dummy = 0;
  EXPECT_DEATH({ Span<int>(nullptr, &dummy); }, "");
  EXPECT_DEATH({ Span<int>(&dummy, nullptr); }, "");
}

TEST(OpaqueValueTest, NoWrap) {
  std::array<int, 2> dummy = {};
  EXPECT_DEATH({ Span<int>(&dummy[1], &dummy[0]); }, "");
}

TEST(OpaqueValueTest, MakeSpanArray) {
  std::array<int, 10> dummy = {};
  ASSERT_EQ(dummy.data(), GetBase(MakeSpan(dummy)));
  ASSERT_EQ(dummy.data() + dummy.size(), GetLimit(MakeSpan(dummy)));
}

TEST(OpaqueValueTest, MakeSpanConstArray) {
  const std::array<int, 10> dummy = {};
  ASSERT_EQ(dummy.data(), GetBase(MakeSpan(dummy)));
  ASSERT_EQ(dummy.data() + dummy.size(), GetLimit(MakeSpan(dummy)));
}

TEST(OpaqueValueTest, MakeSpanVector) {
  std::vector<int> dummy(10);
  ASSERT_EQ(dummy.data(), GetBase(MakeSpan(dummy)));
  ASSERT_EQ(dummy.data() + dummy.size(), GetLimit(MakeSpan(dummy)));
}

TEST(OpaqueValueTest, MakeSpanConstVector) {
  const std::vector<int> dummy(10);
  ASSERT_EQ(dummy.data(), GetBase(MakeSpan(dummy)));
  ASSERT_EQ(dummy.data() + dummy.size(), GetLimit(MakeSpan(dummy)));
}

TEST(OpaqueValueTest, IsEmpty) {
  std::array<int, 10> dummy = {};
  ASSERT_FALSE(IsEmpty(MakeSpan(dummy)));
  ASSERT_TRUE(IsEmpty(Span<int>()));
}

TEST(OpaqueValueTest, GetSize) {
  std::array<int, 10> dummy = {};
  ASSERT_EQ(dummy.size(), GetSize(MakeSpan(dummy)));
  ASSERT_EQ(0, GetSize(Span<int>()));
}

TEST(OpaqueValueTest, GetByteSize) {
  std::array<int, 10> dummy = {};
  ASSERT_EQ(sizeof(int) * dummy.size(), GetByteSize(MakeSpan(dummy)));
  ASSERT_EQ(0, GetByteSize(Span<int>()));
}
