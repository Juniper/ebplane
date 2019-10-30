#include "lib/posix/unique_file_descriptor.h"
#include "gtest/gtest.h"

using namespace posix;

// UniqueFileDescriptor is written based on the assumtion that base::UniqueValue
// is correct and well tested, therefore there isn't much to test here.

TEST(UniqueFileDescriptorTest, DefaultConstructEmpty) {
  UniqueFileDescriptor fd;
  ASSERT_FALSE(fd);
}

TEST(UniqueFileDescriptorTest, InvalidCausesDeath) {
  ASSERT_DEATH({ UniqueFileDescriptor invalid(kInvalidFileDescriptor); }, "");
}

TEST(UniqueFileDescriptor, CloseIsCalled) {
  // TODO: find a way to mock calls to Close().
}
