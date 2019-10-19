#include <gtest/gtest.h>

#include <vector>

#include "src/collections/linked-list.h"

TEST(TestLinkedList, TestPush) {
  LinkedList<int> list;
  auto cases = std::vector<int>({1, 2, 3, 4, 5});

  for (auto i : cases) {
    list.push(i);
  }

  for (size_t i = 0; i < cases.size(); ++i) {
    EXPECT_EQ(cases[i], list[i]);
  }
}
