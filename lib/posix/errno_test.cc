#include "lib/posix/errno.h"
#include "gtest/gtest.h"

using namespace error;
using namespace posix;

TEST(ErrnoTest, MakeCodeFromErrno) {
  EXPECT_EQ(std::make_error_code(std::errc::interrupted),
            MakeCodeFromErrno(EINTR));
}

TEST(ErrnoTest, OkStatusOrCaptureErrnoIfOk) {
  EXPECT_EQ(kOkStatus, OkStatusOrCaptureErrnoIf(false, "unused"));
}

TEST(ErrnoTest, OkStatusOrCaptureErrnoIfError) {
  errno = EINVAL;
  const auto status = OkStatusOrCaptureErrnoIf(true, "some error");
  EXPECT_TRUE(IsError(status));
  EXPECT_EQ("some error", GetText(status));
}