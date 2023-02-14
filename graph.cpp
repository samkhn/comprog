/* Graphs
 * Demos of BFS, DFS, cycle detection with union-find data structure,
 * Single source shortest path with Dijkstras and topological sort.
 */

#include <cstdio>
#include <deque>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef int node;
typedef std::vector<node> path;
std::string print(const path &p);
typedef int weight;
struct edge {
	node node_a;
	node node_b;
	weight weight;
};
typedef std::list<std::pair<node, weight>> adjacency_list;
/* NOTE: Alternative data structures is an adjacency matrix with
 *   std::vector<std::vector<std::pair<node, weight>>; or int** M[][];
 */
struct graph {
	bool dired;
	unsigned node_count;
	unsigned edge_count;
	std::unordered_map<node, adjacency_list> adjacent_nodes;
};

std::string print(const graph &g);
void init(graph &g, bool dired, std::initializer_list<edge> edges);
void add_edge(graph &g, edge e);

enum class search_type {
	BFS,
	DFS
};
path search(graph &g, search_type type, node start);

// Maps node to id of what set it belongs to
// A node will map to itself it is is the designated member of the set
typedef std::unordered_map<node, node> union_find;
node find_parent(union_find &parents, node node);
void merge(union_find &parents, node from, node to);
bool has_cycle(const graph &g);

// TODO: graph MST(const graph &g);
// TODO: path TopoSortByDeadline(
//   const graph &g, const std::vector<int, std::pair<int, int>> &schedule);
path shortest_path(const graph &g, node from, node to);
path toposort(const graph &g);

std::string print(const graph &g)
{
	std::string elements = "";
	elements.append("graph: |V| = ");
	elements.append(std::to_string(g.node_count));
	elements.append(", |E| = ");
	elements.append(std::to_string(g.edge_count));
	elements.append(", Dired? ");
	elements.append(std::to_string(g.dired));
	elements.append(".\nElements:\n");
	for (auto kv : g.adjacent_nodes) {
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

std::string print(const path &p)
{
	std::string spath = "";
	for (const auto& e : p) {
		spath.append(std::to_string(e));
		spath.append(" ");
	}
	return spath;
}

void init(graph &g, bool dired, std::initializer_list<edge> edges)
{
	g.dired = dired;
	g.node_count = 0;
	g.edge_count = 0;
	for (auto edge_it = edges.begin(); edge_it != edges.end(); edge_it++)
		add_edge(g, *edge_it);
}

void add_edge(graph &g, edge e)
{
	if (e.node_b == -1)
		g.adjacent_nodes[e.node_a];
	else
		g.adjacent_nodes[e.node_a].push_back(
			std::make_pair(e.node_b, e.weight));
	g.node_count = g.adjacent_nodes.size();
	g.edge_count++;
}

path search(graph &g, search_type type, node start)
{
	path p;
	std::deque<node> q;
	std::unordered_set<node> seen;
	node current = start;
	q.push_back(current);
	while (!q.empty()) {
		if (type == search_type::BFS) {
			current = q.front();
			q.pop_front();
		} else {
			current = q.back();
			q.pop_back();
		}
		if (seen.count(current))
			continue;
		p.push_back(current);
		seen.insert(current);
		auto an_it = g.adjacent_nodes.find(current);
		if (an_it == g.adjacent_nodes.end())
			continue;
		auto neighbors = an_it->second;
		for (auto n = neighbors.begin(); n != neighbors.end(); n++)
			q.push_back(n->first);
	}
	return p;
}

node find_parent(union_find &parents, node node)
{
	if (parents[node] != node)
		return find_parent(parents, parents[node]);
	return node;
}

void merge(union_find &parents, node from, node to)
{
	parents[find_parent(parents, to)] = find_parent(parents, from);
}

bool has_cycle(const graph &g)
{
	union_find parent;
	for (auto node : g.adjacent_nodes)
		parent[node.first] = node.first;
	for (auto u : g.adjacent_nodes) {
		auto neighbors = u.second;
		for (auto n = neighbors.begin(); n != neighbors.end(); n++) {
			node l = find_parent(parent, u.first);
			node r = find_parent(parent, n->first);
			if (l == r)
				return true;
			merge(parent, l, r);
		}
	}
	return false;
}

// Shortest path from a source node to any node with Dijkstra's
path shortest_path(const graph &g, node from, node to)
{
	std::unordered_set<node> seen;
	std::vector<node> pred_node(g.node_count+1, -1);
	std::vector<weight> pred_weight(g.node_count+1, 1e9);
	pred_weight[from] = 0;
	std::priority_queue<
		std::pair<node, weight>,
		std::vector<std::pair<node, weight>>,
		std::greater<std::pair<node, weight>>> q;
	q.push(std::make_pair(from, 0));
	node u, v; weight w;
	std::pair<node, weight> scanning;
	while (!q.empty()) {
		scanning = q.top();
		q.pop();
		u = scanning.first;
		if (seen.count(u))
			continue;
		seen.insert(u);
		auto an_it = g.adjacent_nodes.find(u);
		if (an_it == g.adjacent_nodes.end())
			continue;
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
	path path;
	node current = to;
	while (current != from) {
		path.push_back(current);
		current = pred_node[current];
	}
	path.push_back(from);
	std::reverse(path.begin(), path.end());
	return path;
}

void ts_impl(graph &g, path &ts, std::unordered_set<node> &visited, node n)
{
	visited.insert(n);
	auto neighbors = g.adjacent_nodes.find(n);
	if (neighbors != g.adjacent_nodes.end()) {
		for (auto neighbor = neighbors->second.begin();
		     neighbor != neighbors->second.end(); neighbor++) {
			if (visited.count(neighbor->first))
				continue;
			ts_impl(g, ts, visited, neighbor->first);
		}
	}
	ts.push_back(n);
}

path toposort(graph &g)
{
	path ts;
	std::unordered_set<node> visited;
	for (auto u : g.adjacent_nodes) {
		if (visited.count(u.first))
			continue;
		ts_impl(g, ts, visited, u.first);
	}
	std::reverse(ts.begin(), ts.end());
	return ts;
}

path toposortJob(graph &g, const std::vector<std::pair<int, int>> &deadlines)
{
	return {};
}

int main()
{
	graph ug;
	init(ug, /*dired=*/false, /*edges=*/{
			{0, 1, 1},
			{0, 2, 1},
			{1, 2, 1},
			{2, 0, 1},
			{2, 3, 1},
			{3, 3, 1}
		});
	printf("Undirected %s\n"
		"BFS from 2: %s\n"
		"DFS from 1: %s\n"
		"Has cycle? %d\n\n",
		print(ug).c_str(),
		print(search(ug, search_type::BFS, 2)).c_str(),
		print(search(ug, search_type::DFS, 1)).c_str(),
		has_cycle(ug));

	graph dg;
	init(dg, /*dired=*/true, /*edges=*/{
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
	printf("Directed %s\n"
	        "BFS from 0: %s\n"
		"DFS from 0: %s\n"
		"Has cycle? %d\n"
		"ShortestPath(0->4): %s\n\n",
		print(dg).c_str(),
		print(search(dg, search_type::BFS, 2)).c_str(),
		print(search(dg, search_type::DFS, 1)).c_str(),
		has_cycle(dg),
		print(shortest_path(dg, 0, 4)).c_str());

	graph dag;
	init(dag, /*dired=*/true, /*edges=*/{
			{5, 2, 1},
			{5, 0, 1},
			{4, 0, 1},
			{4, 1, 1},
			{2, 3, 1},
			{3, 1, 1}
		});
	printf("DAG %s\n"
	        "Has cycle?: %d\n"
	        "TopoSort: %s\n\n",
		print(dag).c_str(),
		has_cycle(dag),
		print(toposort(dag)).c_str());

	// graph job;
	// init(job,
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
	// path want_schedule = {2, 1, 3, 4, 0, 5, 6, 7, 8};
	// std::cout << "\nJob " << print(job) << "\n"
	//           << "Has cycle? " << has_cycle(job) << "\n"
	//           << "Topological order of job.\nGot : "
	//           << print(toposortJob(job, job_time)) << "\n"
	//           << "Want: " << print(want_schedule) << "\n";
	return 0;
}
