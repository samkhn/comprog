// Sliding window demonstration
// For many substring problems, we are given a string and asked to find a
// substring of it that satisfies some restriction.
// General technique is to use a hashmap and 2 pointers.

#if 0   // DO NOT DELETE
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

#include <cstdio>
#include <string>
#include <vector>

std::string LongestSubstrWithAtmostTwoDistinctChars(std::string_view s) {
  std::vector<int> map(128, 0);
  int counter = 0, begin = 0, end = 0, length = 0;
  int returning_begin = 0, returning_end = 0;
  while (end < s.size()) {
    if (map[s[end]] == 0) counter++;
    map[s[end]]++;
    end++;
    while (counter > 2) {
      // At this point we've seen two distinct characters
      if (map[s[begin]] == 1) counter--;
      map[s[begin]]--;
      begin++;
    }
    if (end - begin >= length) {
      length = end - begin;
      returning_begin = begin;
      returning_end = end;
    }
  }
  return std::string(s.substr(returning_begin, returning_end));
}

std::string LongestSubstrWithoutRepeatingChars(std::string_view s) {
  std::vector<int> map(128, 0);
  int counter = 0, begin = 0, end = 0, length = 0;
  int res_begin = 0, res_end = 0;
  while (end < s.size()) {
    if (map[s[end]] > 0) counter++;
    map[s[end]]++;
    end++;
    while (counter > 0) {
      // Prune the repeated substring by changing begin
      if (map[s[begin]] > 1) counter--;
      map[s[begin]]--;
      begin++;
    }
    if (end - begin >= length) {
      length = end - begin;
      res_begin = begin;
      res_end = end;
    }
  }
  return std::string(s.substr(res_begin, res_end));
}

struct SubstrTest {
  std::string name;
  std::string arg;
  std::string want;
};

int main() {
  int testCount = 2;
  SubstrTest tests[] = {{"1EmptyTestArg", "", ""},
                        {"1HelloTestArg", "hello", "llo"}};
  std::string got;
  for (int i = 0; i < testCount; ++i) {
    got = LongestSubstrWithAtmostTwoDistinctChars(tests[i].arg);
    printf("%s %s | Got %s, Want %s\n", tests[i].name.c_str(),
           (got == tests[i].want ? "PASS" : "FAIL"), got.c_str(),
           tests[i].want.c_str());
  }
  SubstrTest tests2[] = {{"2EmptyTestArg", "", ""},
                         {"2HelloTestArg", "hello", "hel"}};
  for (int i = 0; i < testCount; ++i) {
    got = LongestSubstrWithoutRepeatingChars(tests2[i].arg);
    printf("%s %s | Got %s, Want %s\n", tests2[i].name.c_str(),
           (got == tests2[i].want ? "PASS" : "FAIL"), got.c_str(),
           tests2[i].want.c_str());
  }
  return 0;
}
