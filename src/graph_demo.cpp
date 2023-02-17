// Graphs
// Demos of BFS, DFS, cycle detection with union-find data structure,
// Single source shortest path with Dijkstras and topological sort.

#include "include/graph.hpp"

#include <stdio.h>

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

  // TODO: Job schedule demo
  // Graph job;
  // job.Init(/* dired = */ true,
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
  // // job_time[i] means that job or node i begins at job_time[i].first and
  // ends
  // //  at job_time[i].end.
  // std::vector<std::pair<int, int>> job_time = {
  //   {9, 10}, {11, 16}, {17, 18}, {12, 15}, {13, 14}, {1, 8}, {6, 7}, {2, 5},
  //   {3, 4}
  // };
  // Path want_schedule = {2, 1, 3, 4, 0, 5, 6, 7, 8};
  return 0;
}
