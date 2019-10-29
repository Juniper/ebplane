#include <queue>

#include "gtest/gtest.h"
#include "lib/base/unique_value.h"

using namespace base;

TEST(UniqueValueTest, DefaultConstructor) {
  static std::queue<int> cleanups;
  struct Cleanup {
    void operator()(const int value) { cleanups.push(value); }
  };
  { UniqueValue<int, Cleanup> uv; }
  ASSERT_TRUE(cleanups.empty());
}

TEST(UniqueValueTest, ExplicitValueConstructor) {
  static std::queue<int> cleanups;
  struct Cleanup {
    void operator()(const int value) { cleanups.push(value); }
  };
  { UniqueValue<int, Cleanup> uv(10); }  // Cleanup of 'uv' fires here.
  ASSERT_EQ(1, cleanups.size());
  ASSERT_EQ(10, cleanups.front());
}

TEST(UniqueValueTest, MoveConstructor) {
  static std::queue<int> cleanups;
  struct Cleanup {
    void operator()(const int value) { cleanups.push(value); }
  };
  {
    UniqueValue<int, Cleanup> a(10);
    UniqueValue<int, Cleanup> b(
        std::move(a));  // Overwrite valid (cleanup expected).
    UniqueValue<int, Cleanup> c(
        std::move(b));  // Overwrite valid (cleanup expected).
    ASSERT_EQ(10, *c);
    ASSERT_EQ(10, GetValue(c));
  }  // Cleanup of 'c' fires here.
  ASSERT_EQ(1, cleanups.size());
  ASSERT_EQ(10, cleanups.front());
}

TEST(UniqueValueTest, MoveEmpty) {
  static std::queue<int> cleanups;
  struct Cleanup {
    void operator()(const int value) { cleanups.push(value); }
  };
  {
    UniqueValue<int, Cleanup> a;
    UniqueValue<int, Cleanup> b(
        std::move(a));  // Overwrite empty (no cleanup expected).
    UniqueValue<int, Cleanup> c;
    c = std::move(b);  // Overwrite empty (no cleanup expected).
  }
  ASSERT_TRUE(cleanups.empty());
}

TEST(UniqueValueTest, MoveAssignmentOperator) {
  static std::queue<int> cleanups;
  struct Cleanup {
    void operator()(const int value) { cleanups.push(value); }
  };
  {
    UniqueValue<int, Cleanup> a(10);
    UniqueValue<int, Cleanup> b(11);
    UniqueValue<int, Cleanup> c;
    b = std::move(a);  // Overwrite valid (cleanup expected).
    c = std::move(b);  // Overwrite empty (no cleanup expected).
  }                    // Cleanup of 'c' fires here.
  ASSERT_EQ(2, cleanups.size());
  ASSERT_EQ(11, cleanups.front());
  cleanups.pop();
  ASSERT_EQ(10, cleanups.front());
}