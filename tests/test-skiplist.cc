#include <gtest/gtest.h>

#include "src/collections/skiplist.h"

TEST(SkipList, NodeConstrcutor) {
  auto lst = SkipList<int>(std::less<int>());
  lst.insert(1);

  EXPECT_EQ(lst.size(), 1);
}
