#include <array>

#include "gtest/gtest.h"
#include "lib/status.h"

using namespace error;

std::array<Code, 15> kErrorCodes = {
    Code::CANCELLED,
    Code::UNKNOWN,
    Code::INVALID_ARGUMENT,
    Code::DEADLINE_EXCEEDED,
    Code::NOT_FOUND,
    Code::ALREADY_EXISTS,
    Code::PERMISSION_DENIED,
    Code::RESOURCE_EXHAUSTED,
    Code::FAILED_PRECONDITION,
    Code::ABORTED,
    Code::OUT_OF_RANGE,
    Code::UNIMPLEMENTED,
    Code::INTERNAL,
    Code::UNAVAILABLE,
    Code::DATA_LOSS,
};

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
  EXPECT_NE(Status(Code::ABORTED, "foo"), Status(Code::ABORTED, "bar"));
}

TEST(StatusTest, SameStringDifferentCode) {
  EXPECT_NE(Status(Code::ABORTED, "foo"), Status(Code::UNKNOWN, "foo"));
}

TEST(StatusTest, Copy) {
  Status a(Code::ABORTED, "ABORTED");
  Status b(a);
  Status c = b;
  EXPECT_EQ(a, c);
}

TEST(StatusTest, Move) {
  Status a(Code::ABORTED, "ABORTED");
  Status b(a);
  Status c(std::move(b));
  Status d = std::move(c);
  EXPECT_EQ(a, d);
}

TEST(StatusTest, CopyOverwrite) {
  Status a(Code::ABORTED, "ABORTED");
  Status b(Code::UNKNOWN, "UNKNOWN");
  EXPECT_NE(a, b);
  b = a;
  EXPECT_EQ(a, b);
}

TEST(StatusTest, EmptyOverwrite) {
  Status a;
  Status b(Code::UNKNOWN, "UNKNOWN");
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
    EXPECT_EQ(ToString(code),
              GetText(Status(code, std::string(ToString(code)))));
  }
}