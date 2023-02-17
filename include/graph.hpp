#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Weight = int;
using Node = int;
struct Edge {
  Node u;
  Node v;
  Weight weight;
};

using Path = std::vector<Node>;
std::string Print(const Path &p);

class Graph {
 public:
  bool dired;
  std::size_t node_count;
  std::size_t edge_count;
  std::unordered_map<Node, std::list<std::pair<Node, Weight>>> adjacent_nodes;

  std::string Print() const;
  void Init(bool dired, std::initializer_list<Edge> edges);
  void AddEdge(Edge e);
  
  enum class SearchType { BFS, DFS };
  Path Search(SearchType type, Node start) const;
  Path ShortestPath(Node from, Node to) const;
  Path TopoSort();
  
  bool HasCycle() const;

  // TODO: MST
  Graph MST() const;

 private:
  void TopoSortRecurse(Path &ts, std::unordered_set<Node> &visited, Node n);
};


class UnionFind {
 public:
  std::unordered_map<Node, Node> parents;
  void Union(Node from, Node to);
  Node Find(Node of);
};


#endif _GRAPH_HPP_
