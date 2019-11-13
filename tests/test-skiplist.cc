#include <gtest/gtest.h>

#include <string>

#include "src/collections/skiplist.h"

TEST(SkipList, Constrcutor) {
  auto lst = SkipList<std::string, std::string>(std::less<std::string>());
  EXPECT_EQ(lst.size(), 0);
}

TEST(SkipList, Insert) {
  auto lst = SkipList<std::string, std::string>(std::less<std::string>());
  lst.insert("key", "value");
  EXPECT_EQ(lst.size(), 1);
  auto np = lst.search("key");
  EXPECT_EQ(np->value, "value");
  lst.insert("abc", "ABC");
  EXPECT_EQ(lst.size(), 2);
  lst.insert("key", "new value", 1);
  EXPECT_EQ(lst.size(), 2);
  np = lst.search("key");
  EXPECT_EQ(np->value, "new value");
}

TEST(SkipList, InsertLargeAmount) {
  auto lst = SkipList<std::string, std::string>(std::less<std::string>());
  const int N = 2 << 10;
  for (int i = 1; i <= N; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    auto np = lst.insert(key, value);
    EXPECT_EQ(np->value, value);
  }
  EXPECT_EQ(lst.size(), N);
}

TEST(SkipList, Remove) {
  auto lst = SkipList<std::string, std::string>(std::less<std::string>());
  lst.insert("key", "value");
  EXPECT_EQ(lst.size(), 1);
  auto np = lst.search("key");
  EXPECT_EQ(np->value, "value");

  bool ret = lst.remove("key");
  EXPECT_TRUE(ret);
  EXPECT_EQ(lst.size(), 0);
  np = lst.search("key");
  EXPECT_EQ(np, nullptr);
}
