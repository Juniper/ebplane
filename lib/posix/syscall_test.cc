#include <sys/syscall.h>
#include <sys/time.h>

#include "gtest/gtest.h"
#include "lib/posix/syscall.h"

using namespace posix;

TEST(SyscallTest, GetTimeOfDay) {
  timeval tv = {};
  auto status_or = Syscall(__NR_gettimeofday, &tv, nullptr);
  EXPECT_TRUE(IsOk(status_or));
}

TEST(SyscallTest, ReadFailure) {
  auto status_or = Syscall(__NR_read, -1, nullptr, 4096);
  EXPECT_TRUE(IsError(status_or));
}