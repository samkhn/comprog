// Substring search techniques
// Explores rabin karp (uses a rolling hash) and
//  KMP (short for Knuth Morris Pratt).
// Includes some (rather dumb and prob inaccurate) benchmarks.
// Please run the benchmarks many times.
// An interesting observation: on small strings, dumbest algorithm works best.

#include <chrono>
#include <cstdio>
#include <string>
#include <vector>

enum class SearchType {
  DUMB /*O(mn)*/,
  STL /*O(mn)*/,
  RK /*Rabin Karp. Average O(n) but worst case is O(mn)*/,
  KMP /*Knuth Morris Pratt. O(m)preprocessing + O(n)search*/
};

std::string ToString(SearchType a) {
  switch (a) {
    case SearchType::DUMB:
      return "DUMB";
    case SearchType::STL:
      return "STLb";
    case SearchType::RK:
      return "RbKp";
    case SearchType::KMP:
      return "KnMP";
  }
  return "";
}

// TODO: learn how this is a good hash function for strings
// NOTE: this is similar to LCG:
//   https://en.wikipedia.org/wiki/Linear_congruential_generator
// NOTE: 5381 is a large primer number that worked during testing for
//   collisions. Another value that works is 33.
unsigned int DJBHash(std::string_view s) {
  unsigned int hash = 5381, i = 0;
  for (int i = 0; i < s.size(); i++) hash = ((hash << 5) + hash) + s[i];
  return hash;
}

// lps[i] is the length of the longest possible proper prefix at char s[i]
// Needs to be proper aka not include the char in question
// At `lps[j] = i`: if we encounter this char in search and the next char
// fails, we should jump by i spaces to save time.
std::vector<int> LongestProperPrefixTable(std::string_view s) {
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
    } else
      i = lps[i - 1];
  }
  return lps;
}

int findSubstrDumb(std::string_view space, std::string_view query) {
  int i = 0;
  int j = 0;
  while (i < space.size()) {
    while (j < query.size()) {
      if (space[i + j] != query[j]) break;
      if (j == query.size() - 1) return i;
      ++j;
    }
    if (j >= space.size()) return -1;
    ++i;
  }
  return -1;
}

// Works by maintaining a rolling hash. Hash is of a window of data that moves
// with input. Average O(n) bc of rolling hash. Worst case O(mn).
int findSubstrRK(std::string_view space, std::string_view query) {
  unsigned int q_size = (unsigned int)query.size();
  unsigned int q_hash = DJBHash(query);
  unsigned int s_hash = DJBHash(space.substr(0, q_size));
  int last_i = (int)space.size() - q_size + 1;
  for (int i = 0; i < last_i; ++i) {
    if (s_hash == q_hash && !query.compare(space.substr(i, q_size))) return i;
    s_hash = DJBHash(space.substr(i + 1, q_size));
  }
  return -1;
}

int findSubstrKMP(std::string_view space, std::string_view query) {
  std::vector<int> lpp = LongestProperPrefixTable(query);
  int i = 0, j = 0;
  while (i < space.size()) {
    if (space[i] == query[j]) {
      // If the characters match, continue scanning
      // Stop scanning once we reach the end of query
      if (j == query.size() - 1) {
        return i - j;
      }
      i++;
      j++;
      continue;
    }
    // If the chars don't match we need to readjust what window we
    // are scanning.
    // If j != 0, we need to jump to the next appropriate spot using
    // lpp. Check LongestProperPrefixTable() for more details.
    // If j == 0, we can move i up and restart the scan.
    if (j != 0)
      j = lpp[j - 1];
    else
      i++;
  }
  return -1;
}

// Returns:
// >= 0 if valid result
// -1 if not found
// -2 on error
// -3 on unimplemented
int FindSubstr(SearchType algorithm, std::string_view space,
               std::string_view query) {
  if (query.size() == 0) return 0;
  if (query.size() > space.size()) return -1;
  switch (algorithm) {
    case SearchType::STL:
      // TODO(samkhn): This converts size_t to int. Clean this.
      return space.find(query);
    case SearchType::DUMB:
      return findSubstrDumb(space, query);
    case SearchType::RK:
      return findSubstrRK(space, query);
    case SearchType::KMP:
      return findSubstrKMP(space, query);
    default:
      return -3;
  }
  return -2;
}

struct SubstrSearchTest {
  std::string name;
  std::string space;
  std::string query;
  int want;
};
static constexpr int kTestCount = 7;

// TODO: randomize which test runs
void run(SubstrSearchTest *tests, SearchType a) {
  int successes = 0;
  int64_t total = 0;
  for (int i = 0; i < kTestCount; ++i) {
    auto start = std::chrono::steady_clock::now();
    int got = FindSubstr(a, tests[i].space, tests[i].query);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - start;
    bool pass = (got == tests[i].want);
    if (pass) successes++;
    total += elapsed.count();
    printf(
        "%s FindSubstr(%s, %s, %s) | Got: %d. Want %d. "
        "Time: %lld\n",
        (pass ? "PASS" : "FAIL"), ToString(a).c_str(), tests[i].space.c_str(),
        tests[i].query.c_str(), got, tests[i].want, elapsed.count());
  }
  printf("Tests passed: %d / %d. Avg time per test: %lld\n\n", successes,
         kTestCount, total / kTestCount);
}

int main() {
  // First, a look at DJBHash
  std::vector<std::string> hash_tests(
      {"This", "is", "a", "test", "of", "DJBHash", "which", "uses", "5381"});
  for (const auto &t : hash_tests) {
    printf("DJBHash(%s) = %d\n", t.c_str(), DJBHash(t));
  }
  hash_tests = {"g", "gr", "gro", "grow", "growi", "growin", "growing"};
  for (const auto &t : hash_tests) {
    printf("DJBHash(%s) = %d\n", t.c_str(), DJBHash(t));
  }

  // Then, we evaluate various substring searches
  SubstrSearchTest *tests = new SubstrSearchTest[kTestCount]{
      {"EmptyTestCase", "", "", 0},
      {"EmptySearchQuery", "test", "", 0},
      {"EmptySpace", "", "test", -1},
      {"StandardSearchPrefix1char", "hello", "h", 0},
      {"StandardSearchPrefix", "hello", "hel", 0},
      {"StandardSearchMiddle", "hello", "el", 1},
      {"StandardSearchEnd", "hello", "o", 4}};
  run(tests, SearchType::DUMB);
  run(tests, SearchType::STL);
  run(tests, SearchType::RK);
  run(tests, SearchType::KMP);
}
