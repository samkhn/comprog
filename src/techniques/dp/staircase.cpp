// Staircase
// LeetCode 70
// You are climbing a stair case. It takes n steps to reach to the top.
// Each time you can either climb 1 or 2 steps. In how many distinct ways
// can you climb to the top?
// Note: Given n will be a positive integer.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int countWaysToClimb(std::vector<int> &m, int n) {
	if (n >= 0 && n <= 2) {
		return n;
	}
	if (m[n] == 0) {
		int takeOne = countWaysToClimb(m, n - 1);
		int takeTwo = countWaysToClimb(m, n - 2);
		m[n] = takeOne + takeTwo;
	}
	return m[n];
}

int CountWaysToClimbStairs(int n) {
	std::vector<int> m(n + 1, 0);
	return countWaysToClimb(m, n);
}

struct TestCase {
	std::string name;
	int in;
	int want;
};

int main() {
	std::vector<TestCase> tests = {
			{"Ex1", 2, 2},
			{"Ex2", 3, 3},
	};

	for (auto t : tests) {
		if (CountWaysToClimbStairs(t.in) != t.want) {
			std::cout << "FAIL " << t.name << "\n";
		} else {
			std::cout << "PASS " << t.name << "\n";
		}
	}
	return 0;
}
