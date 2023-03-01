// Longest Palindromic Subsequence
// LeetCode 516
// Given a string s, find the longest palindromic subsequence’s length in s.
// You may assume that the maximum length of s is 1000.
// Palindrome := sequence of chars/numbers that read the same backward and
// forward e.g. madam, racecar

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int lps(std::string_view s, std::vector<std::vector<int>> &m, int b, int e) {
  if (b > e) {
    return 0;
  }
  if (b == e) {
    return 1;
  }
  if (m[b][e] == -1) {
    if (s[b] == s[e]) {
      m[b][e] = 2 + lps(s, m, b+1, e-1);
    } else {
      int sub1 = lps(s, m, b+1, e);
      int sub2 = lps(s, m, b, e-1);
      m[b][e] = std::max(sub1, sub2);
    }
  }
  return m[b][e];
}

int LongestPalindromicSequence(std::string_view s) {
  int l = s.size();
  std::vector<std::vector<int>> m(l, std::vector<int>(l, -1));
  return lps(s, m, 0, l-1);
}

struct TestCase {
  std::string name;
  std::string in;
  int want;
};

int main() {
  std::vector<TestCase> tests = {
    {"Ex1", "bbbab", 4},
    {"Ex2", "cbbd", 2},
  };
  for (auto t : tests) {
    if (LongestPalindromicSequence(t.in) != t.want) {
      std::cout << "FAIL " << t.name << "\n";
    } else {
      std::cout << "PASS " << t.name << "\n";
    }
  }
  return 0;
}
