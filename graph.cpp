/* Graphs
 * Demos of BFS, DFS, cycle detection with union-find data structure,
 *   Single source shortest path with Dijkstras and topological sort.
 */

#include <deque>
#include <format>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using Node = int;
using Path = std::vector<Node>;
std::string Print(const Path &p);
using Weight = int;
struct Edge
{
  Node node_a;
  Node node_b;
  Weight weight; 
};
using AdjList = std::list<std::pair<Node, Weight>>;
struct Graph
{
  bool dired;
  unsigned node_count;
  unsigned edge_count;
  // NOTE: Alternative data structures is an adjacency matrix with
  //  std::vector<std::vector<std::pair<Node, Weight>>; or int** M[][];
  std::unordered_map<Node, AdjList> adjacent_nodes;
};

std::string Print(const Graph &g);
void Init(Graph &g, bool dired, std::initializer_list<Edge> edges);
void AddEdge(Graph &g, Edge e);

enum class SearchType { BFS, DFS };
Path Search(Graph &g, SearchType type, Node start);

// For cycle detection
// Maps node to id of what set it belongs to
// A node will map to itself it is is the designated member of the set
using UF = std::unordered_map<Node, Node>;
Node FindParent(UF &parents, Node node);
void Union(UF &parents, Node from, Node to);
bool HasCycle(const Graph &g);

// TODO: Graph MST(const Graph &g);
// TODO: Path TopoSortByDeadline(
//   const Graph &g, const std::vector<int, std::pair<int, int>> &schedule);
Path ShortestPath(const Graph &g, Node from, Node to);
Path TopoSort(const Graph &g);

// Printers
std::string Print(const Graph &g)
{
  std::string elements = "";
  for (auto kv : g.adjacent_nodes) {
    elements.append(std::format("edge {0} ", kv.first));
    for (auto it = kv.second.begin(); it != kv.second.end(); ++it)
      elements.append(std::format("node {0} weight {1} ",
                                  it->first, it->second));
    elements.append("\n");
  }
  return std::format("Graph: |V| = {0}, |E| = {1}, Dired? {2}. Elements:\n{3}",
                     g.node_count, g.edge_count, g.dired, elements);
}

std::string Print(const Path &p)
{
  std::string spath = "";
  for (const auto& e : p) {
    spath.append(std::to_string(e));
    spath.append(" ");
  }
  return spath;
}

// Graph Impl
void Init(Graph &g, bool dired, std::initializer_list<Edge> edges)
{
  g.dired = dired;
  g.node_count = 0;
  g.edge_count = 0;
  for (auto edge_it = edges.begin(); edge_it != edges.end(); edge_it++) {
    AddEdge(g, *edge_it);
  }
}

void AddEdge(Graph &g, Edge e)
{
  if (e.node_b == -1)
    g.adjacent_nodes[e.node_a];
  else
    g.adjacent_nodes[e.node_a].push_back(std::make_pair(e.node_b, e.weight));
  g.node_count = g.adjacent_nodes.size();
  g.edge_count++;
}

// BFS and DFS
Path Search(Graph &g, SearchType type, Node start)
{
  Path path;
  std::deque<Node> visit;
  std::unordered_set<Node> visited;
  Node current = start;
  visit.push_back(current);
  while (!visit.empty()) {
    if (type == SearchType::BFS) {
      current = visit.front();
      visit.pop_front();
    } else {
      current = visit.back();
      visit.pop_back();
    }
    if (visited.contains(current))
      continue;
    path.push_back(current);
    visited.insert(current);
    auto adj_nodes = g.adjacent_nodes.find(current);
    if (adj_nodes != g.adjacent_nodes.end()) {
      for (auto neighbor = adj_nodes->second.begin();
           neighbor != adj_nodes->second.end(); neighbor++) {
        visit.push_back(neighbor->first);
      }
    }
  }
  return path;
}

// Union Find to detect cycles
Node FindParent(UF &parents, Node node)
{
  if (parents[node] != node)
    return FindParent(parents, parents[node]);
  return node;
}

void Union(UF &parents, Node from, Node to)
{
  parents[FindParent(parents, to)] = FindParent(parents, from);
}

bool HasCycle(const Graph &g)
{
  UF parent;
  for (auto node : g.adjacent_nodes)
    parent[node.first] = node.first;
  for (auto kv : g.adjacent_nodes) {
    for (auto it = kv.second.begin(); it != kv.second.end(); ++it) {
      Node l = FindParent(parent, kv.first);
      Node r = FindParent(parent, it->first);
      if (l == r)
        return true;
      Union(parent, l, r);
    }
  }
  return false;
}

// Shortest path from a source node to any node with Dijkstra's
Path ShortestPath(const Graph &g, Node from, Node to)
{
  std::unordered_set<Node> seen;
  std::vector<Node> predecessor_node(g.node_count+1, -1);
  std::vector<Weight> predecessor_weight(g.node_count+1, 1e9);
  predecessor_weight[from] = 0;
  std::priority_queue<
    std::pair<Node, Weight>,
    std::vector<std::pair<Node, Weight>>,
    std::greater<std::pair<Node, Weight>>> q;
  q.push(std::make_pair(from, 0));
  Node u, v; Weight w;
  std::pair<Node, Weight> scanning;
  while (!q.empty()) {
    scanning = q.top(); q.pop();
    u = scanning.first;
    if (seen.contains(u))
      continue;
    seen.insert(u);
    auto neighbors = g.adjacent_nodes.find(u);
    if (neighbors != g.adjacent_nodes.end()) {
      for (auto neighbor = neighbors->second.begin();
           neighbor != neighbors->second.end(); neighbor++) {
        v = neighbor->first;
        w = neighbor->second;
        if (predecessor_weight[v] > predecessor_weight[u] + w) {
          predecessor_weight[v] = predecessor_weight[u] + w;
          predecessor_node[v] = u;
          q.push(std::make_pair(v, predecessor_weight[v]));
        }
      }
    }
  }
  Path path;
  Node current = to;
  while (current != from) {
    path.push_back(current);
    current = predecessor_node[current];
  }
  path.push_back(from);
  std::reverse(path.begin(), path.end());
  return path;
}

void topoSortImpl(Graph &g, Path &ts, std::unordered_set<Node> &visited, Node n)
{
  visited.insert(n);
  auto neighbors = g.adjacent_nodes.find(n);
  if (neighbors != g.adjacent_nodes.end()) {
    for (auto neighbor = neighbors->second.begin();
         neighbor != neighbors->second.end(); neighbor++) {
      if (visited.contains(neighbor->first))
        continue;
      topoSortImpl(g, ts, visited, neighbor->first);
    }
  }
  ts.push_back(n);
}

Path TopoSort(Graph &g)
{
  Path ts;
  std::unordered_set<Node> visited;
  for (auto kv : g.adjacent_nodes) {
    if (visited.contains(kv.first))
      continue;
    topoSortImpl(g, ts, visited, kv.first);
  }
  std::reverse(ts.begin(), ts.end());
  return ts;
}

Path TopoSortJob(Graph &g, const std::vector<std::pair<int, int>> &deadlines)
{
  return {};
}

int main()
{
  Graph ug;
  Init(ug, /* dired = */false,
       {  /* edges = */
         {0, 1, 1},
         {0, 2, 1},
         {1, 2, 1},
         {2, 0, 1},
         {2, 3, 1},
         {3, 3, 1}
       });
  std::cout << "\nUndirected " << Print(ug) << "\n"
            << "BFS from 2:\n" << Print(Search(ug, SearchType::BFS, 2)) << "\n"
            << "DFS from 1:\n" << Print(Search(ug, SearchType::DFS, 1)) << "\n"
            << "Has cycle? " << HasCycle(ug) << "\n";

  Graph dg;
  Init(dg,
         /* dired = */ true,
       { /* edges = */
         {0, 1, 10},
         {0, 2, 5},
         {1, 2, 2},
         {2, 1, 3},
         {1, 3, 1},
         {2, 3, 9},
         {2, 4, 2},
         {3, 4, 4},
         {4, 3, 6},
         {4, 0, 7}
       });
  std::cout << "\nDirected " << Print(dg) << "\n"
            << "BFS from 0:\n" << Print(Search(dg, SearchType::BFS, 0)) << "\n"
            << "DFS from 0:\n" << Print(Search(dg, SearchType::DFS, 0)) << "\n"
            << "Has cycle? " << HasCycle(dg) << "\n"
            << "Shortest path (0->4): "
            << Print(ShortestPath(dg, 0, 4)) << "\n";

  Graph dag;
  Init(dag,
         /* dired = */ true,
       { /* edges = */
         {5, 2, 1},
         {5, 0, 1},
         {4, 0, 1},
         {4, 1, 1},
         {2, 3, 1},
         {3, 1, 1}
       });
  std::cout << "\nDAG " << Print(dag) << "\n"
            << "Has cycle? " << HasCycle(dag) << "\n"
            << "Topo sort. Got:  " << Print(TopoSort(dag)) << "\n";
  
  // Graph job;
  // Init(job,
  //        /* dired = */ true,
  //      { /* edges = */
  //        {0, -1, 1},
  //        {2, 4, 1},
  //        {1, 3, 1},
  //        {1, 4, 1},
  //        {3, 6, 1},
  //        {5, 6, 1},
  //        {5, 7, 1},
  //        {7, 8, 1},
  //        {6, 8, 1}
  //      });
  // // job_time[i] means that job or node i begins at job_time[i].first and ends
  // //  at job_time[i].end.
  // std::vector<std::pair<int, int>> job_time = {
  //   {9, 10}, {11, 16}, {17, 18}, {12, 15}, {13, 14}, {1, 8}, {6, 7}, {2, 5}, {3, 4}
  // };
  // Path want_schedule = {2, 1, 3, 4, 0, 5, 6, 7, 8};
  // std::cout << "\nJob " << Print(job) << "\n"
  //           << "Has cycle? " << HasCycle(job) << "\n"
  //           << "Topological order of job.\nGot : "
  //           << Print(TopoSortJob(job, job_time)) << "\n"
  //           << "Want: " << Print(want_schedule) << "\n";
	return 0;
}
