/* Substring search techniques
 *
 * Explores rabin karp (uses a rolling hash) and
 *  KMP (short for Knuth Morris Pratt).
 * Includes some (rather dumb and prob inaccurate) benchmarks.
 * Please run the benchmarks many times.
 *
 * An interesting observation: on small strings, dumbest algorithm works best.
 */

#include <chrono>
#include <cstdio>
#include <string>
#include <vector>

enum class search_type {
	DUMB /*O(mn)*/,
	STL  /*O(mn)*/,
	RK   /*Rabin Karp. Average O(n) but worst case is O(mn)*/,
	KMP  /*Knuth Morris Pratt. O(m)preprocessing + O(n)search*/
};

std::string to_string(search_type a)
{
	switch(a) {
	case search_type::DUMB:
		return "DUMB";
	case search_type::STL:
		return "STLb";
	case search_type::RK:
		return "RbKp";
	case search_type::KMP:
		return "KnMP";
	}
	return "";
}

/* TODO: learn how this is a good hash function for strings
 * NOTE: this is similar to LCG:
 *   https://en.wikipedia.org/wiki/Linear_congruential_generator
 * NOTE: 5381 is a large primer number that worked during testing for
 *   collisions. Another value that works is 33.
 */
unsigned int djbhash(std::string_view s)
{
	unsigned int hash = 5381, i = 0;
	for (int i = 0; i < s.size(); i++)
		hash = ((hash << 5) + hash) + s[i];
	return hash;
}

/* lps[i] is the length of the longest possible proper prefix at char s[i]
 * Needs to be proper aka not include the char in question
 * At `lps[j] = i`: if we encounter this char in search and the next char
 * fails, we should jump by i spaces to save time.
 */
std::vector<int> longest_proper_prefix_table(std::string_view s)
{
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

int _find_substr_dumb(std::string_view space, std::string_view query)
{
	int i = 0;
	int j = 0;
	while (i < space.size()) {
		while (j < query.size()) {
			if (space[i+j] != query[j])
				break;
			if (j == query.size()-1)
				return i;
			++j;
		}
		if (j >= space.size())
			return -1;
		++i;
	}
	return -1;
}

/* Works by maintaining a rolling hash. Hash is of a window of data that moves
 * with input. Average O(n) bc of rolling hash. Worst case O(mn).
 */
int _find_substr_rk(std::string_view space, std::string_view query)
{
	unsigned int q_size = query.size();
	unsigned int q_hash = djbhash(query);
	unsigned int s_hash = djbhash(space.substr(0, q_size));
	int last_i = space.size() - q_size + 1;
	for (int i = 0; i < last_i; ++i) {
		if (s_hash == q_hash && !query.compare(space.substr(i, q_size)))
				return i;
		s_hash = djbhash(space.substr(i+1, q_size));
	}
	return -1;
}

int _find_substr_kmp(std::string_view space, std::string_view query)
{
	std::vector<int> lpp = longest_proper_prefix_table(query);
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
		/* If the chars don't match we need to readjust what window we
		 * are scanning.
		 * If j != 0, we need to jump to the next appropriate spot using
		 * lpp. Check longest_proper_prefix_table() for more details.
		 * If j == 0, we can move i up and restart the scan.
		 */
		if (j != 0)
			j = lpp[j - 1];
		else
			i++;
	}
	return -1;
}

/* >= 0 if valid result
 * -1 if not found
 * -2 on error
 * -3 on unimplemented
 */
int find_substr(search_type algorithm,
		std::string_view space, std::string_view query)
{
	if (query.size() == 0)
		return 0;
	if (query.size() > space.size())
		return -1;
	switch (algorithm) {
	case search_type::STL:
		return space.find(query);
	case search_type::DUMB:
		return _find_substr_dumb(space, query);
	case search_type::RK:
		return _find_substr_rk(space, query);
	case search_type::KMP:
		return _find_substr_kmp(space, query);
	default:
		return -3;
	}
	return -2;
}

struct substr_search_test {
	std::string name;
	std::string space;
	std::string query;
	int want;
};
static constexpr int kTestCount = 7;

// TODO: randomize which test runs
void run(substr_search_test *tests, search_type a)
{
	int successes = 0;
	int64_t total = 0;
	for (int i = 0; i < kTestCount; ++i) {
		auto start = std::chrono::steady_clock::now();
		int got = find_substr(a, tests[i].space, tests[i].query);
		auto end = std::chrono::steady_clock::now();
		auto elapsed = end-start;
		bool pass = (got == tests[i].want);
		if (pass)
			successes++;
		total += elapsed.count();
		printf("%s find_substr(%s, %s, %s) | Got: %d. Want %d. "
			"Time: %lld\n", (pass ? "PASS" : "FAIL"),
			to_string(a).c_str(),
			tests[i].space.c_str(),
			tests[i].query.c_str(),
			got, tests[i].want, elapsed.count());
	}
	printf("Tests passed: %d / %d. Avg time per test: %lld\n\n",
		successes, kTestCount, total/kTestCount);
}

int main()
{
	substr_search_test *tests = new substr_search_test[kTestCount]
		{
		{"EmptyTestCase",             "",      "",      0},
		{"EmptySearchQuery",          "test",  "",      0},
		{"EmptySpace",                "" ,     "test", -1},
		{"StandardSearchPrefix1char", "hello", "h",     0},
		{"StandardSearchPrefix",      "hello", "hel",   0},
		{"StandardSearchMiddle",      "hello", "el",    1},
		{"StandardSearchEnd",         "hello", "o",     4}
		};
	run(tests, search_type::DUMB);
	run(tests, search_type::STL );
	run(tests, search_type::RK  );
	run(tests, search_type::KMP );
}
