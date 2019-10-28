#include "lib/error/assign_or_return.h"
#include "gtest/gtest.h"
#include "lib/error/errno.h"
#include "lib/error/status_or.h"

using namespace error;

const Status kDefault(MakeCodeFromErrno(ECHILD), "default");

TEST(TryAssignTest, CopyableStatusOr) {
  constexpr auto fn = [](StatusOr<int> s) -> StatusOr<int> {
    int a = 0;
    ASSIGN_OR_RETURN(a, s);
    ASSIGN_OR_RETURN(const int b, s);
    ASSIGN_OR_RETURN(const auto c, s);
    return a + b + c;
  };
  EXPECT_EQ(99, GetValue(fn(33)));
  EXPECT_TRUE(IsError(fn(kDefault)));
  EXPECT_EQ(kDefault, GetStatus(fn(kDefault)));
}

TEST(TryAssignTest, MoveOnlyStatusOr) {
  constexpr auto fn = [](StatusOr<std::unique_ptr<int>> s) -> StatusOr<int> {
    ASSIGN_OR_RETURN(const auto a, std::move(s));
    return *a;
  };
  EXPECT_EQ(99, GetValue(fn(std::make_unique<int>(99))));
  EXPECT_TRUE(IsError(fn(kDefault)));
  EXPECT_EQ(kDefault, GetStatus(fn(kDefault)));
}

TEST(TryTest, UnguardedIf) {
  constexpr auto fn = [](const bool fail) {
    int tmp = 0;
    if (fail) ASSIGN_OR_RETURN(tmp, StatusOr<int>(kDefault));
    return kOkStatus;
  };
  EXPECT_EQ(kOkStatus, fn(false));
  EXPECT_EQ(kDefault, fn(true));
}

TEST(TryTest, NestedTry) {
  EXPECT_EQ(kDefault, []() -> Status {
    ASSIGN_OR_RETURN(const auto tmp, []() -> StatusOr<int> {
      ASSIGN_OR_RETURN(const auto tmp, StatusOr<int>(kDefault));
      (void)tmp;
      return kOkStatus;
    }());
    (void)tmp;
    return kOkStatus;
  }());
}

TEST(TryTest, RogueTemporary) {
  EXPECT_EQ(kDefault, []() {
    int _try_assign_tmp = 0;
    ASSIGN_OR_RETURN(const auto tmp, StatusOr<int>(kDefault));
    (void)_try_assign_tmp;
    (void)tmp;
    return kOkStatus;
  }());
}