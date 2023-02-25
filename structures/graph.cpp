// Graphs
// Demos of BFS, DFS, cycle detection with union-find data structure,
// Single source shortest path with Dijkstras and topological sort.

#include <algorithm>
#include <deque>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <utility>
#include <vector>

using Node = int;

class UnionFind {
 public:
  std::vector<Node> parents;

  void Union(Node a, Node b) {
    parents[Find(b)] = Find(a);
  }
  
  Node Find(Node n) {
    if (parents[n] == n) {
      return n;
    }
    return Find(parents[n]);
  }
};

using Weight = int;

struct Edge {
  Node u;
  Node v;
  Weight weight;
};

using Path = std::vector<Node>;

std::string Print(const Path &p) {
  std::string spath = "";
  for (const auto &e : p) {
    spath.append(std::to_string(e));
    spath.append(" ");
  }
  return spath;
}

class Graph {
 public:
  bool dired;
  std::size_t node_count;
  std::size_t edge_count;
  std::unordered_map<Node, std::list<std::pair<Node, Weight>>> adjacent_nodes;

  std::string Print() const {
    std::string elements = "";
    elements.append("graph: |V| = ");
    elements.append(std::to_string(this->node_count));
    elements.append(", |E| = ");
    elements.append(std::to_string(this->edge_count));
    elements.append(", Dired? ");
    elements.append(std::to_string(this->dired));
    elements.append(".\nElements:\n");
    for (auto kv : this->adjacent_nodes) {
      elements.append("\tedge ");
      elements.append(std::to_string(kv.first));
      elements.append(" ");
      for (auto it = kv.second.begin(); it != kv.second.end(); ++it) {
        elements.append("node ");
        elements.append(std::to_string(it->first));
        elements.append(" ");
        elements.append("weight ");
        elements.append(std::to_string(it->second));
        elements.append(" ");
      }
      elements.append("\n");
    }
    return elements;
  }
  void Init(bool dired, std::initializer_list<Edge> edges) {
    this->dired = dired;
    this->node_count = 0;
    this->edge_count = 0;
    for (auto edge_it = edges.begin(); edge_it != edges.end(); edge_it++) {
      AddEdge(*edge_it);
    }
  }
  void AddEdge(Edge e) {
    if (e.v == -1) {
      this->adjacent_nodes[e.u];
    } else {
      this->adjacent_nodes[e.u].push_back(
          std::make_pair(e.v, e.weight));
      this->adjacent_nodes[e.v];
    }
    this->node_count = this->adjacent_nodes.size();
    this->edge_count++;
  }

  // In BFS and DFS mode, it'll return a path
  // In FindCycle mode, it'll return a path with {1} or {0} where 1 indicates
  // a cycle was detected, 0 means no cycle found.
  enum class SearchType { BFS, DFS, FindCycle };
  Path Search(SearchType type, Node start) const {
    Path p;
    std::deque<Node> q;
    std::unordered_set<Node> seen;
    Node current = start;
    q.push_back(current);
    while (!q.empty()) {
      if (type == SearchType::BFS) {
        current = q.front();
        q.pop_front();
      } else {
        current = q.back();
        q.pop_back();
      }
      if (seen.count(current)) {
        if (type == SearchType::FindCycle) {
          return {1};
        }
        continue;
      }
      p.push_back(current);
      seen.insert(current);
      auto an_it = this->adjacent_nodes.find(current);
      if (an_it == this->adjacent_nodes.end()) {
        continue;
      }
      auto neighbors = an_it->second;
      for (auto n = neighbors.begin(); n != neighbors.end(); n++) {
        q.push_back(n->first);
      }
    }
    if (type == SearchType::FindCycle)
      return {0};
    return p;
  }
  
  Path ShortestPath(Node from, Node to) const {
    std::unordered_set<Node> seen;
    std::vector<Node> pred_node(this->node_count + 1, -1);
    std::vector<Weight> pred_weight(this->node_count + 1, (int)1e9);
    pred_weight[from] = 0;
    std::priority_queue<std::pair<Node, Weight>,
                        std::vector<std::pair<Node, Weight>>,
                        std::greater<std::pair<Node, Weight>>>
        q;
    q.push(std::make_pair(from, 0));
    Node u, v;
    Weight w;
    std::pair<Node, Weight> scanning;
    while (!q.empty()) {
      scanning = q.top();
      q.pop();
      u = scanning.first;
      if (seen.count(u)) {
        continue;
      }
      seen.insert(u);
      auto an_it = this->adjacent_nodes.find(u);
      if (an_it == this->adjacent_nodes.end()) {
        continue;
      }
      auto neighbor = an_it->second;
      for (auto n = neighbor.begin(); n != neighbor.end(); n++) {
        v = n->first;
        w = n->second;
        if (pred_weight[v] > pred_weight[u] + w) {
          pred_weight[v] = pred_weight[u] + w;
          pred_node[v] = u;
          q.push(std::make_pair(v, pred_weight[v]));
        }
      }
    }
    Path path;
    Node current = to;
    while (current != from) {
      path.push_back(current);
      current = pred_node[current];
    }
    path.push_back(from);
    std::reverse(path.begin(), path.end());
    return path;
  }
  
  Path TopoSort() {
    Path ts;
    std::unordered_set<Node> visited;
    for (auto u : this->adjacent_nodes) {
      if (visited.count(u.first)) {
        continue;
      }
      TopoSortRecurse(ts, visited, u.first);
    }
    std::reverse(ts.begin(), ts.end());
    return ts;
  }
  
  bool HasCycle() const {
    if (!dired) {
      UnionFind uf;
      uf.parents.resize(node_count);
      for (auto node : this->adjacent_nodes) {
        uf.parents[node.first] = node.first;
      }
      for (auto u : this->adjacent_nodes) {
        auto neighbors = u.second;
        for (auto n = neighbors.begin(); n != neighbors.end(); n++) {
          Node l = uf.Find(u.first);
          Node r = uf.Find(n->first);
          printf("Edge {%d %d}. Parents are %d %d. ", u.first, n->first, l, r);
          if (l == r) {
            printf("Parents are same, edge found\n");
            return true;
          }
          printf("Parents diff. Union(%d, %d) ", l, r);
          uf.Union(l, r);
          for (int i = 0; i < uf.parents.size(); i++) {
            printf("%d ", uf.parents[i]);
          }
          printf("\n");
        }
      }
    } else {
      Path cycle;
      for (auto node : this->adjacent_nodes) {
        cycle = Search(SearchType::FindCycle, node.first);
        if (cycle[0] == 1) {
          return true;
        }
      }
    }
    return false;
  }

  // TODO: MST
  Graph MST() const;

 private:
  void TopoSortRecurse(Path &ts, std::unordered_set<Node> &visited, Node n) {
    visited.insert(n);
    auto neighbors = this->adjacent_nodes.find(n);
    if (neighbors != this->adjacent_nodes.end()) {
      for (auto neighbor = neighbors->second.begin();
           neighbor != neighbors->second.end(); neighbor++) {
        if (visited.count(neighbor->first)) {
          continue;
        }
        TopoSortRecurse(ts, visited, neighbor->first);
      }
    }
    ts.push_back(n);
  }
};

int main() {
  Graph ug;
  ug.Init(/*dired=*/false, /*edges=*/
       {{0, 1, 1}, {0, 2, 1}, {1, 2, 1}, {2, 0, 1}, {2, 3, 1}, {3, 3, 1}});
  printf(
      "Undirected %s\n"
      "BFS from 2: %s\n"
      "DFS from 1: %s\n"
      "Has cycle? %d\n\n",
      ug.Print().c_str(), Print(ug.Search(Graph::SearchType::BFS, 2)).c_str(),
      Print(ug.Search(Graph::SearchType::DFS, 1)).c_str(), ug.HasCycle());

  Graph dg;
  dg.Init(/*dired=*/true, /*edges=*/
       {{0, 1, 10},
        {0, 2, 5},
        {1, 2, 2},
        {2, 1, 3},
        {1, 3, 1},
        {2, 3, 9},
        {2, 4, 2},
        {3, 4, 4},
        {4, 3, 6},
        {4, 0, 7}});
  printf(
      "Directed %s\n"
      "BFS from 0: %s\n"
      "DFS from 0: %s\n"
      "Has cycle? %d\n"
      "ShortestPath(0->4): %s\n\n",
      dg.Print().c_str(), Print(dg.Search(Graph::SearchType::BFS, 2)).c_str(),
      Print(dg.Search(Graph::SearchType::DFS, 1)).c_str(), dg.HasCycle(),
      Print(dg.ShortestPath(0, 4)).c_str());

  Graph dag;
  dag.Init(/*dired=*/true, /*edges=*/
       {{5, 2, 1}, {5, 0, 1}, {4, 0, 1}, {4, 1, 1}, {2, 3, 1}, {3, 1, 1}});
  printf(
      "DAG %s\n"
      "Has cycle?: %d\n"
      "TopoSort: %s\n\n",
      dag.Print().c_str(), dag.HasCycle(), Print(dag.TopoSort()).c_str());

  return 0;
}
