#include "lib/posix/unique_file_descriptor.h"
#include "gtest/gtest.h"

using namespace posix;

TEST(UniqueFileDescriptorTest, DefaultConstruct) { UniqueFileDescriptor fd; }

TEST(UniqueFileDescriptorTest, Invalid) {
  UniqueFileDescriptor fd(kInvalidFileDescriptor);
}