#include "include/graph.hpp"

#include <deque>
#include <queue>

std::string Print(const Path &p) {
  std::string spath = "";
  for (const auto &e : p) {
    spath.append(std::to_string(e));
    spath.append(" ");
  }
  return spath;
}

std::string Graph::Print() const {
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

void Graph::Init(bool dired, std::initializer_list<Edge> edges) {
  this->dired = dired;
  this->node_count = 0;
  this->edge_count = 0;
  for (auto edge_it = edges.begin(); edge_it != edges.end(); edge_it++) {
    AddEdge(*edge_it);
  }
}

void Graph::AddEdge(Edge e) {
  if (e.v == -1) {
    this->adjacent_nodes[e.u];
  } else {
    this->adjacent_nodes[e.u].push_back(
        std::make_pair(e.v, e.weight));
  }
  this->node_count = this->adjacent_nodes.size();
  this->edge_count++;
}

Path Graph::Search(SearchType type, Node start) const {
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
    if (seen.count(current)) continue;
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
  return p;
}

Path Graph::ShortestPath(Node from, Node to) const {
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

void Graph::TopoSortRecurse(
    Path &ts, std::unordered_set<Node> &visited, Node n) {
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

Path Graph::TopoSort() {
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

Node UnionFind::Find(Node of) {
  if (parents[of] != of) {
    return Find(parents[of]);
  }
  return of;
}

void UnionFind::Union(Node from, Node to) {
  parents[Find(to)] = Find(from);
}

bool Graph::HasCycle() const {
  UnionFind uf;
  for (auto node : this->adjacent_nodes) {
    uf.parents[node.first] = node.first;
  }
  for (auto u : this->adjacent_nodes) {
    auto neighbors = u.second;
    for (auto n = neighbors.begin(); n != neighbors.end(); n++) {
      Node l = uf.Find(u.first);
      Node r = uf.Find(n->first);
      if (l == r) {
        return true;
      }
      uf.Union(l, r);
    }
  }
  return false;
}
