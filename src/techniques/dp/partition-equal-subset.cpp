// partition equal subset sum
// 0/1 Knapsack demonstration
// LeetCode 416 - partition equal subset sum
// Given a non-empty array of positive integers, find if the array can be
// partitioned into two subsets s.t. that the sum of elements in each
// subset are equal.

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int canPartition(std::vector<int> &nums, std::vector<std::vector<int>> &m,
                 int start_index, int sum) {
  if (sum == 0) {
    return 1;
  }
  if (nums.size() == 0 || start_index >= nums.size()) {
    return 0;
  }
  if (m[start_index][sum] == -1) {
    if (nums[start_index] <= sum) {
      if (canPartition(nums, m, start_index + 1, sum - nums[start_index])) {
        m[start_index][sum] = 1;
        return 1;
      }
    }
    m[start_index][sum] = canPartition(nums, m, start_index + 1, sum);
  }
  return m[start_index][sum];
}

int EqualPartitionSumR(std::vector<int> &nums) {
  int sum = std::reduce(nums.begin(), nums.end());
  if (sum % 2) {
    return 0;
  }
  sum = (int)(sum / 2);
  int length = nums.size();
  std::vector<std::vector<int>> m(length, std::vector<int>(sum + 1, -1));
  if (canPartition(nums, m, 0, sum)) {
    return 1;
  }
  return 0;
}

int EqualPartitionSum(std::vector<int> &nums) {
  int sum = std::reduce(nums.begin(), nums.end());
  if (sum % 2) {
    return 0;
  }
  sum = (int)(sum / 2);
  int length = nums.size();
  std::vector<std::vector<bool>> m(length, std::vector<bool>(sum + 1, false));
  for (int i = 0; i < length; ++i) {
    m[i][0] = true;
  }
  for (int i = 1; i < sum + 1; ++i) {
    m[0][i] = (nums[0] == i);
  }
  for (int i = 1; i < length; ++i) {
    for (int j = 1; j < sum + 1; ++j) {
      if (m[i - 1][j]) {
        m[i][j] = m[i - 1][j];
      } else if (j >= nums[i]) {
        m[i][j] = m[i - 1][j - nums[i]];
      }
    }
  }
  return m[length - 1][sum];
}

struct TestCase {
  std::string name;
  std::vector<int> in;
  bool want;
};

int main() {
  std::vector<TestCase> test = {
      {"Ex1", {1, 5, 11, 5}, true},
      {"Ex2", {1, 2, 3, 5}, false},
      {"Ex3", {1, 5, 11, 3}, false},
  };

  for (auto t : test) {
    if (EqualPartitionSumR(t.in) != t.want) {
      std::cout << "Memo FAIL: " << t.name << "\n";
    } else {
      std::cout << "Memo PASS: " << t.name << "\n";
    }
    if (EqualPartitionSum(t.in) != t.want) {
      std::cout << "Tab FAIL: " << t.name << "\n";
    } else {
      std::cout << "Tab PASS: " << t.name << "\n";
    }
  }
  return 0;
}
