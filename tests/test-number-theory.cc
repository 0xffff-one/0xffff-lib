#include "src/math/number-theory.h"

#include <gtest/gtest.h>
#include <vector>
#include <utility>

TEST(TestGcd, TestCoprime) {
  std::vector<std::pair<int,int>> cases = {
    std::pair<int,int>(1, 7),
    std::pair<int,int>(13, 7),
    std::pair<int,int>(9, 7),
    std::pair<int,int>(7, 13),
  };

  for(auto tuple: cases) {
    int a = tuple.first;
    int b = tuple.second;
    EXPECT_EQ(1, gcd(a, b));
  }
}
