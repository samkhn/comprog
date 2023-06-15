// TODO: K-way Merge Sort
// e.g. Given two sorted integer arrays, nums1 and nums2, and the number of
//	data elements in each array, m and n, implement a function that merges
// the 	second array into the first one. You have to modify numes1 in place.

#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct Node {
  int value;
  Node *next;
};

std::vector<int> MergeSorted(const std::vector<Node *> &lists) {
  std::vector<int> s;
  std::priority_queue<std::pair<int, Node *>,
                      std::vector<std::pair<int, Node *>>,
                      std::greater<std::pair<int, Node *>>>
      pq;
  for (int i = 0; i < lists.size(); ++i) {
    pq.push(std::make_pair(lists[i]->value, lists[i]));
  }
  std::pair<int, Node *> p;
  while (!pq.empty()) {
    p = pq.top();
    pq.pop();
    s.push_back(p.first);
    if (p.second->next) {
      p.first = p.second->next->value;
      p.second = p.second->next;
      pq.push(p);
    }
  }
  return s;
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

struct Test {
  std::string name;
  std::vector<Node *> in;
  std::vector<int> want;
};

int main() {
  std::vector<Test> tests = {
      {"Single element", {new Node{1, nullptr}}, {1}},
      {"Single list",
       {new Node{1, new Node{2, new Node{3, nullptr}}}},
       {1, 2, 3}},
      {"Two lists",
       {
           new Node{1, new Node{2, new Node{3, nullptr}}},
           new Node{1, new Node{2, new Node{3, nullptr}}},
       },
       {1, 1, 2, 2, 3, 3}},
      {"LC lists",
       {
           new Node{1, new Node{4, new Node{5, nullptr}}},
           new Node{1, new Node{3, new Node{4, nullptr}}},
           new Node{2, new Node{6, nullptr}},
       },
       {1, 1, 2, 3, 4, 4, 5, 6}}};
  std::vector<int> got;
  for (const auto &t : tests) {
    got = MergeSorted(t.in);
    if (!Equal(got, t.want)) {
      std::cout << "Failed test " << t.name << ". Got " << ToString(got)
                << ". Want " << ToString(t.want) << "\n";
    } else {
      std::cout << "Passed test " << t.name << "\n";
    }
  }
}
