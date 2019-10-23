#include <map>
#include <string>

#include "gtest/gtest.h"
#include "lib/base/opaque_value.h"

DEFINE_OPAQUE_VALUE(int, OpaqueInt)

TEST(OpaqueValueTest, ConstructAndCopy) {
  OpaqueInt a(1);
  OpaqueInt b(a);
  OpaqueInt c = b;
  EXPECT_EQ(a, c);
}

TEST(OpaqueValueTest, GetValue) { EXPECT_EQ(15, GetValue(OpaqueInt(15))); }

TEST(OpaqueValueTest, Equality) {
  EXPECT_EQ(OpaqueInt(1), OpaqueInt(1));
  EXPECT_NE(OpaqueInt(1), OpaqueInt(2));
}

TEST(OpaqueValueTest, CompareImplementsLess) {
  EXPECT_TRUE(OpaqueInt::Compare()(OpaqueInt(1), OpaqueInt(2)));
}

TEST(OpaqueValueTest, Compare) {
  using Map = std::map<OpaqueInt, std::string, OpaqueInt::Compare>;
  Map m;
  m[OpaqueInt(1)] = "1";
  m[OpaqueInt(2)] = "2";
  EXPECT_EQ("1", m[OpaqueInt(1)]);
  EXPECT_EQ("2", m[OpaqueInt(2)]);
}
