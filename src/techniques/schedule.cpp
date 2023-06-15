// Job scheduling

#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Returns schedule without all jobs if cycle detected.
std::vector<int> Schedule(int job_count,
                          const std::vector<std::pair<int, int>> &ordering) {
  std::vector<int> ts;
  // source will be node(s) with in-degree 0
  std::vector<int> indegrees(job_count, 0);
  std::vector<std::vector<int>> prereqs(job_count,
                                        std::vector<int>(job_count, 0));
  for (const auto &p : ordering) {
    prereqs[p.first][p.second] = 1;
    indegrees[p.second]++;
  }
  std::deque<int> q;
  for (int i = 0; i < indegrees.size(); ++i) {
    if (!indegrees[i]) {
      q.push_back(i);
    }
  }
  std::vector<bool> seen(job_count, false);
  int current;
  while (!q.empty()) {
    current = q.front();
    q.pop_front();
    if (seen[current]) return {-1};
    seen[current] = true;
    ts.push_back(current);
    const std::vector<int> &neighbors = prereqs[current];
    for (int i = 0; i < neighbors.size(); i++) {
      if (!prereqs[current][i]) continue;
      indegrees[i]--;
      if (indegrees[i] == 0) q.push_back(i);
    }
  }
  return ts;
}

bool Equal(const std::vector<int> &l, const std::vector<int> &r) {
  if (l.size() != r.size()) {
    return false;
  }
  for (int i = 0; i < l.size(); ++i) {
    if (l.at(i) != r.at(i)) {
      return false;
    }
  }
  return true;
}

std::string ToString(const std::vector<int> &v) {
  std::string s;
  if (!v.empty()) {
    s.append(std::to_string(v[0]));
    for (int i = 1; i < v.size(); ++i) {
      s.append(" ");
      s.append(std::to_string(v[i]));
    }
  }
  return s;
}

struct ScheduleTest {
  std::string name;
  // job_timing[i] means that job or node i begins at job_timing[i].first
  // and ends at job_time[i].second
  int num_jobs;
  std::vector<std::pair<int, int>> job_timing;
  std::vector<int> want;
};

int main() {
  // TODO: this test should just check that some set of nodes come before others
  std::vector<ScheduleTest> tests = {
      {"Simple", 2, {{0, 1}}, {0, 1}},
      {"Cycle", 2, {{0, 1}, {1, 0}}, {-1}},
      {"Cycle2", 3, {{0, 1}, {2, 1}, {1, 0}}, {-1}},
      //{"Multiple", 5, {{4, 1}, {4, 2}, {2, 3}, {2, 1}}, {0, 4, 2, 1, 3}},
  };
  std::vector<int> got;
  for (const auto &t : tests) {
    got = Schedule(t.num_jobs, t.job_timing);
    if (!Equal(got, t.want)) {
      std::cout << "Failed " << t.name << ". Got: " << ToString(got)
                << ". Want: " << ToString(t.want) << "\n";
    } else {
      std::cout << "Passed " << t.name << "\n";
    }
  }
  return 0;
}
