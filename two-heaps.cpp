/* Two heaps.
 * Inspiration: https://emre.me/coding-patterns/two-heaps/
 *
 * You can find the median of numbers by maintaining two heaps (a max+min).
 * Other problems might ask you to use a max+max or min+min heap.
 *
 */

#include <format>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


struct Result
{
  int status; // 1 if fine, 0 if not.
  float value;
};

std::string Print(const Result &r)
{
  return std::format( "{0} {1} ", r.status, r.value );
}

using MaxQ = std::priority_queue<int, std::vector<int>, std::less<int>>;
using MinQ = std::priority_queue<int, std::vector<int>, std::greater<int>>;
struct List
{
  int c;
  MaxQ left_side_queue;
  MinQ right_side_queue;
};
List *NewList();
int Insert(List *l, int v);
Result Median(List *l);
Result leftTop(List *l);
Result rightTop(List *l);

List *NewList()
{
  List *l = new List;
  l->c = 0;
  return l;
}

int Insert(List *l, int v)
{
  if (!l)
    return -1;
  Result m = Median(l);
  if (!m.status)
    return -1;
  if (m.value == 0 || v <= m.value) {
    l->left_side_queue.push(v);
    Result left = leftTop(l);
    if (!left.status)
      return -1;
    if (v < left.value) {
      l->right_side_queue.push(left.value);
      l->left_side_queue.pop();
    }
  } else {
    l->right_side_queue.push(v);
    Result right = rightTop(l);
    if (!right.status)
      return -1;
    if (v > right.value) {
      l->left_side_queue.push(right.value);
      l->right_side_queue.pop();      
    }
  }
  l->c++;
  return 1;
}

Result leftTop(List *l)
{
  if (!l)
    return Result{0, 0};
  if (l->left_side_queue.empty())
    return Result{1, 0};
  return Result{1, (float)l->left_side_queue.top()};
}

Result rightTop(List *l)
{
  if (!l)
    return Result{0, 0};
  if (l->right_side_queue.empty())
    return Result{1, 0};
  return Result{1, (float)l->right_side_queue.top()};
}

Result Median(List *l)
{
  if (!l)
    return Result{0, 0};
  if (l->c == 0)
    return Result{1, 0};
  Result left_top_result = leftTop(l);
  if (!left_top_result.status)
    return Result{0, 0};
  Result right_top_result = rightTop(l);
  if (!right_top_result.status)
    return Result{0, 0};
  if (l->c % 2) {
    return left_top_result;
  }
  return Result{1, ((left_top_result.value + right_top_result.value) / 2)};
}


int main()
{
  List *l = NewList();
  Result s = Median(l);
  if (s.value != 0) {
    std::cout << "Median({}). "
              << "Got: "<< Print(s) << ". Want: {1 0}\n";
    std::cout << "L element count: " << l->c << "\n";
    return -1;
  }
  if (!Insert(l, 3)) {
    std::cout << "Insert(l, 3). " << "Got: fail. Want: success\n";
    return -1;
  }
  s = Median(l);
  if (s.value != 3) {
    std::cout << "Median({3}). "
              << "Got: { "<< Print(s) << "}. Want: { 1 3 }\n";
    std::cout << "L element count: " << l->c << "\n";
    return -1;
  }
  if (!Insert(l, 1)) {
    std::cout << "Insert(l, 1). " << "Got: fail. Want: success\n";
    return -1;
  }
  s = Median(l);
  if (s.value != 2) {
    std::cout << "Median({1, 3}). "
              << "Got: { "<< Print(s) << "}. Want: { 1 2 }\n";
    std::cout << "L element count: " << l->c << "\n";
    return -1;
  }	
  return 0;
}
