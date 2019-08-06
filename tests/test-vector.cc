#include <gtest/gtest.h>
#include "src/collections/vector.h"

TEST(TestVec, TestSize) {
  Vec<int> vec;
  EXPECT_EQ(0, vec.size());
}

TEST(TestVec, TestIsEmpty) {
  Vec<int> vec;
  EXPECT_EQ(true, vec.is_empty());
}

TEST(TestVec, TestIndexOp) {
  Vec<int> vec;
  vec.push(2333);

  EXPECT_EQ(2333, vec[0]);
}

TEST(TestVec, TestPush) {
  Vec<int> vec;
  int cases[] = {0, 1, 2, 3, 4, 5, 6, 7};

  for (auto idx : cases) {
    vec.push(idx);
  }

  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i, vec[i]);
  }
}

TEST(TestVec, TestPop) {
  Vec<int> vec;
  vec.push(233);

  EXPECT_EQ(233, vec.pop().value());
  EXPECT_EQ(std::nullopt, vec.pop());
}

TEST(TestVec, TestIterator)
{
  Vec<int> vec;
  vec.push(1);
  vec.push(2);
  vec.push(3);
  vec.push(4);
  vec.push(5);
  int counter = 1;

  for(Vec<int>::iterator it = vec.begin(); it != vec.end(); it++)
  {
	EXPECT_EQ(counter, *it);
	counter++;
  }
}

