// 01 Knapsack
// 0/1 := cannot break choice down
// Given a set of objects, each w/ a value and a weight, what is the maximum
// value we can obtain by selecting a subset s.t. the sum of weights does not
// exceed some [knapsack] capacity.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// In each pair, first is value, second is weight.
using Knapsack = std::vector<std::pair<int, int>>;

int MaxKnapsackWeight(const Knapsack &os, int capacity) {
  int object_count = os.size();
  std::vector<std::vector<int>> m(object_count + 1,
                                  std::vector<int>(capacity + 1, 0));
  for (int i = 1; i <= object_count; ++i) {
    for (int j = 0; j <= capacity; ++j) {
      if (os[i - 1].second > j) {
        m[i][j] = m[i - 1][j];
      } else {
        m[i][j] = std::max(m[i - 1][j],
                           os[i - 1].first + m[i - 1][j - os[i - 1].second]);
      }
    }
  }
  return m[object_count][capacity];
}

struct TestCase {
  std::string name;
  Knapsack in_objects;
  int in_capacity;
  int want;
};

int main() {
  std::vector<TestCase> tests = {
      {"Ex1", {}, 1, 0},
      {"Ex2", {{2, 3}, {2, 1}, {4, 3}, {5, 4}, {3, 2}}, 7, 10},
  };
  for (auto t : tests) {
    if (MaxKnapsackWeight(t.in_objects, t.in_capacity) != t.want) {
      std::cout << "FAIL " << t.name << "\n";
    } else {
      std::cout << "PASS " << t.name << "\n";
    }
  }
  return 0;
}
