#include <gtest/gtest.h>

#include <utility>
#include <vector>

#include "src/math/number-theory.h"

TEST(TestGcd, TestCoprime) {
  std::vector<std::pair<int, int>> cases = {
      std::pair<int, int>(1, 7),   std::pair<int, int>(13, 7),
      std::pair<int, int>(9, 7),   std::pair<int, int>(7, 13),
      std::pair<int, int>(13, 21),
  };

  for (auto tuple : cases) {
    int a = tuple.first;
    int b = tuple.second;
    EXPECT_EQ(1, gcd(a, b));
  }
}

TEST(TestGcd, TestNormalCases) {
  std::vector<std::vector<int>> cases = {
      std::vector<int>({2, 8, 6}),
      std::vector<int>({21, 42, 63}),
      std::vector<int>({13, 78, 169}),
      std::vector<int>({11, 99, 121}),
  };

  for (auto triple : cases) {
    int expected = triple[0];
    int a = triple[1];
    int b = triple[2];
    EXPECT_EQ(expected, gcd(a, b));
  }
}
