#include "lib/error/return_if_error.h"
#include "gtest/gtest.h"
#include "lib/error/status.h"

using namespace error;

const Status kDefault(Code(1), "default");
const Status kOther(Code(2), "other");

TEST(TryTest, Status) {
  constexpr auto fn = [](const Status s) {
    RETURN_IF_ERROR(s);
    return kDefault;
  };
  EXPECT_EQ(kDefault, fn(kOkStatus));
  EXPECT_EQ(kOther, fn(kOther));
}

TEST(TryTest, UnguardedIf) {
  constexpr auto fn = [](const bool fail) {
    if (fail) RETURN_IF_ERROR(kDefault);
    return kOkStatus;
  };
  EXPECT_EQ(kOkStatus, fn(false));
  EXPECT_EQ(kDefault, fn(true));
}

TEST(TryTest, NestedTry) {
  EXPECT_EQ(kDefault, []() {
    RETURN_IF_ERROR([]() -> Status {
      RETURN_IF_ERROR(kDefault);
      return kOkStatus;
    }());
    return kOkStatus;
  }());
}

TEST(TryTest, RogueTemporary) {
  EXPECT_EQ(kDefault, []() {
    int _try_tmp = 0;
    RETURN_IF_ERROR(kDefault);
    (void)_try_tmp;
    return kOkStatus;
  }());
}