#include "gtest/gtest.h"
#include "lib/error/status_or.h"

using namespace error;

constexpr Code kCancelled(3);

TEST(StatusOrTest, Construct) {
  Status cancelled(kCancelled);
  StatusOr<int> a{cancelled};
  EXPECT_TRUE(IsError(a));
  EXPECT_EQ(cancelled, GetStatus(a));
  StatusOr<int> b(15);
  EXPECT_TRUE(IsOk(b));
  EXPECT_EQ(15, GetValue(b));
}

TEST(StatusOrTest, Copy) {
  StatusOr<int> a(15);
  StatusOr<int> b(a);
  StatusOr<int> c = b;
  EXPECT_EQ(a, c);
}

TEST(StatusOrTest, Move) {
  StatusOr<std::unique_ptr<int>> a = std::make_unique<int>(15);
  StatusOr<std::unique_ptr<int>> b(std::move(a));
  StatusOr<std::unique_ptr<int>> c = std::move(b);
  EXPECT_TRUE(IsOk(c));
  EXPECT_EQ(15, *GetValue(c));
}

TEST(StatusOrTest, GetLValue) {
  StatusOr<int> tmp(15);
  EXPECT_EQ(15, GetValue(tmp));
}

TEST(StatusOrTest, GetConstLValue) {
  const StatusOr<int> tmp(15);
  EXPECT_EQ(15, GetValue(tmp));
}

TEST(StatusOrTest, GetRValue) {
  StatusOr<int> tmp(15);
  EXPECT_EQ(15, GetValue(std::move(tmp)));
}

TEST(StatusOrTest, GetConstRValue) {
  const StatusOr<int> tmp(15);
  EXPECT_EQ(15, GetValue(std::move(tmp)));
}
