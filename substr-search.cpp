// Substring search techniques
// Explores rabin karp (uses a rolling hash) and
//  KMP (short for Knuth Morris Pratt).
// Includes some (rather dumb and prob inaccurate) benchmarks.
//  BM do demonstrate that at small n, algorithms aren't necessarily faster.

#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

enum class SearchAlgorithm {
  DUMB /*O(mn)*/,
  STL  /*O(mn)*/,
  RK   /*Rabin Karp. Average O(n) but worst case is O(mn)*/,
  KMP  /*Knuth Morris Pratt. O(m)preprocessing + O(n)search*/
};
std::string SearchAlgoToStr(SearchAlgorithm a) {
  switch(a) {
  case SearchAlgorithm::DUMB: return "DUMB";
  case SearchAlgorithm::STL:  return "STLb";
  case SearchAlgorithm::RK:   return "RbKp";
  case SearchAlgorithm::KMP:  return "KnMP";
  }
  return "ERROR(could not convert search algorithm type)";
}


// TODO: learn how this is a good hash function for strings
// NOTE: this is similar to LCG:
//   https://en.wikipedia.org/wiki/Linear_congruential_generator
// NOTE: 5381 is a large primer number that worked during testing for
//   collisions. Another value that works is 33.
unsigned int DJBHash(std::string_view s) {
  unsigned int hash = 5381, i = 0;
  for (int i = 0; i < s.size(); i++)
    hash = ((hash << 5) + hash) + s[i];
  return hash;
}


// Preprocesses the query.
// lps[i] is the length of the longest possible proper prefix.
// Needs to be proper (not include the char in question).
// At `lps[j] = i`: if we encounter this char in search and the next char fails,
//  we should jump by i spaces to save time.
std::vector<int> generateLongestProperPrefixTable(std::string_view s) {
  std::vector<int> lps(s.length(), 0);
  int i = 0;
  int j = 1;
  while (j < s.size()) {
    if (s[j] == s[i]) {
      i++;
      lps[j] = i;  
      j++;
    } else if (i == 0) {
      lps[j] = 0;
      j++;
    } else {
      i = lps[i - 1];
    }
  }
  return lps;
}


// Returns -3 unimplemented, -2 on error, -1 if not found and valid result if
// the value is greater than or equal to 0.
int FindSubstr(
  SearchAlgorithm algorithm,
  std::string_view SearchSpace, std::string_view Query) {
  if (Query.size() > SearchSpace.size()) return -1;
  if (Query.size() == 0) return 0;
  switch (algorithm) {
  case SearchAlgorithm::DUMB: {
    std::size_t search_it = 0;
    while (search_it < SearchSpace.size()) {
      if (SearchSpace[search_it] == Query[0]) {
	bool matchExists = true;
	for (int query_it = 0; query_it < Query.size(); ++query_it) {
	  if (SearchSpace[search_it+query_it] != Query[query_it]) {
	    matchExists = false;
	    break;
	  }
	}
	if (matchExists) return search_it;
      }
      search_it++;
    }
    return -1;
  }
  case SearchAlgorithm::STL:
    return SearchSpace.find(Query);
  case SearchAlgorithm::RK: {
    // Works by maintaining a rolling hash. Hash is of a window of data that
    // moves with input. Average O(n) bc of rolling hash. Worst case O(mn).
    int i = 0;
    unsigned int qSize = Query.size();
    unsigned int queryHash = DJBHash(Query);
    unsigned int searchSpaceHash = DJBHash(SearchSpace.substr(i, qSize));
    int lastPossibleMatchIndex = SearchSpace.size() - qSize + 1;
    for (; i < lastPossibleMatchIndex; ++i) {
      if (searchSpaceHash == queryHash) {
	if (Query.compare(SearchSpace.substr(i, qSize)) == 0)
	  return i;
      }
      searchSpaceHash = DJBHash(SearchSpace.substr(i+1, qSize));
    }
    return -1;
  }
  case SearchAlgorithm::KMP: {
    std::vector<int> longestProperPrefix =
      generateLongestProperPrefixTable(Query);
    int search_it = 0, query_it = 0;
    while (search_it < SearchSpace.size()) {
      if (SearchSpace[search_it] == Query[query_it]) {
	// If the characters match, continue scanning
	// Stop scanning once we reach the end of query
	if (query_it == Query.size() - 1) {
	  return search_it - query_it;
	}
	search_it++;
	query_it++;
      } else {
	// If the chars don't match we need to readjust what window we are
	// scanning
	if (query_it != 0) {
	  // If query_it > 0, we need to jump to the next appropriate spot.
	  // Check generateLongestProperPrefixTable() for more details.
	  query_it = longestProperPrefix[query_it - 1];
	} else {
	  // If query_it == 0, we can move search_it up and restart the scan
	  search_it++;
	}
      }
    }
    return -1;
  }
  default:
    break;
  }
  return -2;
}


struct SubstrSearchTestCase {
  std::string Name;
  std::string SearchSpace;
  std::string Query;
  int Want;
};

// TODO: randomize which test runs
void SubstrSearchTestAlgorithm(
  SearchAlgorithm a, SubstrSearchTestCase *tests, int testCount) {
  auto start = std::chrono::steady_clock::now();
  int got;
  for (int i = 0; i < testCount; ++i) {
    got = FindSubstr(a, tests[i].SearchSpace, tests[i].Query);
    std::cout << std::format("{0}: FindSubstr({1}, {2}): "
			     "Got: {3}. Want: {4}\n",
			     (got == tests[i].Want ? "PASS" : "FAIL"),
			     SearchAlgoToStr(a), tests[i].Name,
			     got, tests[i].Want);
  }
  auto end = std::chrono::steady_clock::now();
  auto elapsed = end - start;
  std::cout << std::format("  BM: FindSubstr({0}) time: {1}. "
			   "avg per case: {2}\n", SearchAlgoToStr(a),
			   elapsed.count(), elapsed.count()/testCount);
}

int main() {
  constexpr int testCount = 7;
  SubstrSearchTestCase *tests = new SubstrSearchTestCase[testCount]{
    {"EmptyTestCase",             "",      "",      0},
    {"EmptySearchQuery",          "test",  "",      0},
    {"EmptySearchSpace",          "" ,     "test", -1},
    {"StandardSearchPrefix1char", "hello", "h",     0},
    {"StandardSearchPrefix",      "hello", "hel",   0},
    {"StandardSearchMiddle",      "hello", "el",    1},
    {"StandardSearchEnd",         "hello", "o",     4}
  };
  SubstrSearchTestAlgorithm(SearchAlgorithm::DUMB, tests, testCount);
  SubstrSearchTestAlgorithm(SearchAlgorithm::STL,  tests, testCount);
  SubstrSearchTestAlgorithm(SearchAlgorithm::RK,   tests, testCount);
  SubstrSearchTestAlgorithm(SearchAlgorithm::KMP,  tests, testCount);
}
