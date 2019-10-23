#include <array>
#include <limits>

#include "gtest/gtest.h"
#include "lib/error/status.h"

using namespace error;

std::array<Code, 4> kErrorCodes = {
    Code(1),
    Code(-1),
    Code(std::numeric_limits<int>::min()),
    Code(std::numeric_limits<int>::max()),
};

constexpr Code kAborted(1);
constexpr Code kUnknown(2);

TEST(StatusTest, CodeIsOk) {
  EXPECT_TRUE(IsOk(kOkCode));
  for (const auto code : kErrorCodes) {
    EXPECT_FALSE(IsOk(code));
  }
}

TEST(StatusTest, CodeIsError) {
  EXPECT_FALSE(IsError(kOkCode));
  for (const auto code : kErrorCodes) {
    EXPECT_TRUE(IsError(code));
  }
}

TEST(StatusTest, StatusIsOk) {
  EXPECT_TRUE(IsOk(Status(kOkCode)));
  for (const auto code : kErrorCodes) {
    EXPECT_FALSE(IsOk(Status(code)));
  }
}

TEST(StatusTest, StatusIsError) {
  EXPECT_FALSE(IsError(Status(kOkCode)));
  for (const auto code : kErrorCodes) {
    EXPECT_TRUE(IsError(Status(code)));
  }
}

TEST(StatusTest, Inequality) {
  for (const auto code : kErrorCodes) {
    EXPECT_NE(kOkCode, code);
  }
}

TEST(StatusTest, SameCodeDifferentString) {
  EXPECT_NE(Status(kAborted, "foo"), Status(kAborted, "bar"));
}

TEST(StatusTest, SameStringDifferentCode) {
  EXPECT_NE(Status(kAborted, "foo"), Status(kUnknown, "foo"));
}

TEST(StatusTest, DefaultOk) {
  EXPECT_TRUE(IsOk(Status()));
}

TEST(StatusTest, Copy) {
  Status a(kAborted, "ABORTED");
  Status b(a);
  Status c = b;
  EXPECT_EQ(a, c);
}

TEST(StatusTest, Move) {
  Status a(kAborted, "ABORTED");
  Status b(a);
  Status c(std::move(b));
  Status d = std::move(c);
  EXPECT_EQ(a, d);
}

TEST(StatusTest, CopyOverwrite) {
  Status a(kAborted, "ABORTED");
  Status b(kUnknown, "UNKNOWN");
  EXPECT_NE(a, b);
  b = a;
  EXPECT_EQ(a, b);
}

TEST(StatusTest, EmptyOverwrite) {
  Status a;
  Status b(kUnknown, "UNKNOWN");
  EXPECT_TRUE(IsOk(a));
  EXPECT_NE(a, b);
  b = a;
  EXPECT_EQ(a, b);
}

TEST(StatusTest, GetCode) {
  EXPECT_EQ(kOkCode, GetCode(Status(kOkCode)));
  for (const auto code : kErrorCodes) {
    EXPECT_EQ(code, GetCode(Status(code)));
  }
}

TEST(StatusTest, GetText) {
  EXPECT_EQ("", GetText(Status(kOkCode)));
  for (const auto code : kErrorCodes) {
    EXPECT_EQ(std::to_string(GetValue(code)),
              GetText(Status(code, std::to_string(GetValue(code)))));
  }
}