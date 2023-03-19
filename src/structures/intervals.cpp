// Intervals (array subsets)
//
// Here are the three scenarios you'll see:
// (1) a and b do not overlap: a.end < b.begin
//	[  a	][	b  ]
// (2) a and b overlap, b ends after a: a.begin <= b.begin & a.end < b.end
//	[  a	]
//		[  b	]
// (3) a overlaps completely with b: a.begin <= b.begin & a.end >= b.end
//	[		a		]
//		[ b ]
//
// Merging two intervals?
// if (a.end < b.begin)
//	 no overlap
// if (a.end > b.end)
//	 total overlap
// some overlap. Can merge via (a.begin, b.end)

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Interval = std::pair<int, int>;

std::vector<Interval> Merge(std::vector<Interval> intervals) {
	if (intervals.empty()) {
		return {};
	}
	std::sort(intervals.begin(), intervals.end(),
						[](Interval l, Interval r) { return l.first < r.first; });
	std::vector<Interval> s;
	for (int i = 0; i < intervals.size(); ++i) {
		if (s.empty() || s.back().second < intervals[i].first) {
			s.push_back(intervals[i]);
		} else {
			s.back().second = std::max(s.back().second, intervals[i].second);
		}
	}
	return s;
}

bool Equal(const std::vector<Interval> &l, const std::vector<Interval> &r) {
	if (l.size() != r.size()) {
		return false;
	}
	for (int i = 0; i < l.size(); ++i) {
		if (l.at(i).first != r.at(i).first || l.at(i).second != r.at(i).second) {
			return false;
		}
	}
	return true;
}

struct MergeTest {
	std::string name_;
	std::vector<Interval> in;
	std::vector<Interval> want;
};

int main() {
	std::vector<MergeTest> tests = {
			{"Empty", {}, {}},
			{"Single", {{0, 10}}, {{0, 10}}},
			{"No overlap", {{0, 3}, {5, 10}}, {{0, 3}, {5, 10}}},
			{"End to end", {{0, 5}, {5, 10}}, {{0, 10}}},
			{"Some", {{0, 7}, {4, 10}}, {{0, 10}}},
			{"Overwhelming", {{0, 10}, {4, 7}}, {{0, 10}}},
			{"Unsorted", {{4, 7}, {0, 10}}, {{0, 10}}},
			{"Mix",
			 {{3, 5}, {0, 1}, {1, 3}, {13, 14}, {16, 17}},
			 {{0, 5}, {13, 14}, {16, 17}}}};
	for (const auto &t : tests) {
		if (!Equal(Merge(t.in), t.want)) {
			std::cout << "Failed test: " << t.name_ << "\n";
		} else {
			std::cout << "Passed test: " << t.name_ << "\n";
		}
	}
	return 0;
}
