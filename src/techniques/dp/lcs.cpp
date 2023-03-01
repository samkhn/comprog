// Longest Common Subsequence
// LeetCode 1143
// Given two strings text1 and text2, return the length of their longest
// common subsequence. A common subsequence of two strings is a subsequence
// that is common to both strings. If there is no common subsequence, return 0.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int LongestCommonSubsequence(std::string_view s1, std::string_view s2) {
  int s1s = s1.size();
  int s2s = s2.size();
  int max_length = 0;
  std::vector<std::vector<int>> m(s1s + 1, std::vector<int>(s2s + 1, 0));
  for (int i = 1; i <= s1s; ++i) {
    for (int j = 1; j <= s2s; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        m[i][j] = 1 + m[i - 1][j - 1];
      } else {
        m[i][j] = std::max({m[i - 1][j], m[i][j - 1]});
      }
      max_length = std::max(max_length, m[i][j]);
    }
  }
  return max_length;
}

struct TestCase {
  std::string name;
  std::string in1;
  std::string in2;
  int want;
};

int main() {
  std::vector<TestCase> tests = {
    {"Ex1", "abcde", "ace", 3},
    {"Ex2", "abc", "abc", 3},
    {"Ex3", "abc", "d", 0},
  };
  for (auto t : tests) {
    if (LongestCommonSubsequence(t.in1, t.in2) != t.want) {
      std::cout << "FAIL " << t.name << "\n";
    } else {
      std::cout << "PASS " << t.name << "\n";
    }
  }
  return 0;
}
