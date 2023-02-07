// Primer on Array's Sliding Window
// Source: https://discuss.leetcode.com/topic/30941/here-is-a-10-line-that-can-solve-most-substring-problems
// For many substring problems, we are given a string and asked to find a
// substring of it that satisfies some restriction.
// General technique is to use a hashmap and 2 pointers.
#if 0  // DO NOT DELETE
int find_substring(std::string s) {
  std::vector<int> map(128, 0);  // Optionally initialize this
  int begin = 0, end = 0;
  int counter, length = 0;
  while (end < s.size()) {
    if (map[s[end]] /*some condition like >/<1*/) {
      // Modify counter here
      // Counter will usually be used to test invariant
    }
    // Modify end and its value in the map
    while (/*counter condition that violates invariant*/) {
      // Update length here if finding minimum
      // Increase begin to meet invariant
      if (map[s[begin]] /*some condition like >/<1*/) {
	// Modify counter here to later test invariant
      }
      // Modify begin and its value in the map
    }
    // Update length here if finding maximum
  }
  return length;
}
#endif  // DO NOT DELETE

#include <format>
#include <iostream>
#include <string>
#include <vector>

std::string LongestSubstrWithAtMostTwoDistinctChars(std::string_view s) {
  std::vector<int> map(128, 0);
  int counter = 0, begin = 0, end = 0, length = 0;
  int returning_begin = 0, returning_end = 0;
  while (end < s.size()) {
    if (map[s[end]] == 0)
      counter++;
    map[s[end]]++;
    end++;
    while (counter > 2) {
      // At this point we've seen two distinct characters
      if (map[s[begin]] == 1) {
	counter--;
      }
      map[s[begin]]--;
      begin++;
    }
    if (end-begin >= length) {
      length = end-begin;
      returning_begin = begin;
      returning_end = end;
    }
  }
  return std::string(s.substr(returning_begin, returning_end));
}

std::string LongestSubstWithoutRepeatingChars(std::string_view s) {
  std::vector<int> map(128, 0);
  int counter = 0, begin = 0, end = 0, length = 0;
  int res_begin = 0, res_end = 0;
  while (end < s.size()) {
    if (map[s[end]] > 0)
      counter++;
    map[s[end]]++;
    end++;
    while (counter > 0) {
      // Prune the repeated substring by changing begin
      if (map[s[begin]] > 1) {
	counter--;
      }
      map[s[begin]]--;
      begin++;
    }
    if (end-begin >= length) {
      length = end-begin;
      res_begin = begin;
      res_end = end;
    }
  }
  return std::string(s.substr(res_begin, res_end));
}

struct ArrayWindowTest {
  std::string Name;
  std::string Data;
  std::string Want;
};

int main() {
  int testCount = 2;
  ArrayWindowTest tests[] = {
    {"1EmptyTestCase", "", ""},
    {"1HelloTestCase", "hello", "llo"}
  };
  std::string got;
  for (int i = 0; i < testCount; ++i) {
    got = LongestSubstrWithAtMostTwoDistinctChars(tests[i].Data);
    std::cout << std::format("{0}: Got: {1}. Want: {2}. {3}\n",
			     tests[i].Name, got, tests[i].Want,
			     (got == tests[i].Want ? "PASS" : "FAIL"));
  }
  ArrayWindowTest tests2[] = {
    {"2EmptyTestCase", "", ""},
    {"2HelloTestCase", "hello", "hel"}
  };
  for (int i = 0; i < testCount; ++i) {
    got = LongestSubstWithoutRepeatingChars(tests2[i].Data);
    std::cout << std::format("{0}: Got: {1}. Want: {2}. {3}\n",
			     tests2[i].Name, got, tests2[i].Want,
			     (got == tests2[i].Want? "PASS" : "FAIL"));
  }
  return 0;
}
