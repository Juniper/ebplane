#include "gtest/gtest.h"
#include "lib/error/errno.h"

using namespace error;

class MyCategory : public std::error_category {
 public:
  const char* name() const noexcept override { return "MyCategory"; }
  std::string message(int ev) const noexcept override { return "My Message"; }
};

TEST(CodeTest, Ok) {
  EXPECT_TRUE(IsOk(kOkCode));
  EXPECT_FALSE(IsError(kOkCode));
}

TEST(CodeTest, CustomCategory) {
  MyCategory category;
  std::error_code code(0, category);
  EXPECT_EQ("MyCategory", category.name());
  EXPECT_EQ("My Message", code.message());
}