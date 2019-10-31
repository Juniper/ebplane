#include <linux/bpf.h>

#include "gtest/gtest.h"
#include "lib/bpf/map_create.h"
#include "lib/bpf/map_lookup_element.h"
#include "lib/bpf/map_update_element.h"

using namespace bpf;

TEST(MapCreateTest, EndToEnd) {
  using Key = int;
  using Value = std::pair<int, int>;
  constexpr size_t kMaxElements = 8;
  auto map = MapCreate<Key, Value>(BPF_MAP_TYPE_HASH, kMaxElements);
  ASSERT_TRUE(IsOk(map));
  const auto fd = GetValue(std::move(map));
  Key key = 400;
  Value value = {600, 900};
  const auto update = MapUpdateElement(*fd, key, value);
  ASSERT_TRUE(IsOk(update));
  const auto lookup = MapLookupElement<Key, Value>(*fd, key);
  ASSERT_TRUE(IsOk(lookup));
  ASSERT_EQ(value, GetValue(lookup));
  ASSERT_TRUE(IsError(MapLookupElement<Key, Value>(*fd, 401)));
}