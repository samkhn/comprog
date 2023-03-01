// Fib w/ dynamic programming

#include <iostream>
#include <unordered_map>
#include <vector>

int DumbFib(int n) {
  if (!n || n == 1) {
    return n;
  }
  return DumbFib(n - 1) + DumbFib(n - 2);
}

inline const std::unordered_map<int, int> kInitMemo = {{0, 0}, {1, 1}};

int memoFib(std::unordered_map<int, int> &m, int n) {
  auto it = m.find(n);
  if (it != m.end()) {
    return it->second;
  }
  m[n] = memoFib(m, n - 1) + memoFib(m, n - 2);
  return m[n];
}

int MemoFib(int n) {
  std::unordered_map m = kInitMemo;
  return memoFib(m, n);
}

int TabFib(int n) {
  std::vector<int> v(n + 1, 0);
  v[1] = 1;
  for (int i = 2; i <= n; ++i) {
    v[i] = v[i - 1] + v[i - 2];
  }
  return v[n];
}

int main() {
  std::cout << "DumbFib(10)=" << DumbFib(10) << "\n";
  std::cout << "MemoFib(10)=" << MemoFib(10) << "\n";
  std::cout << "TabFib(10)=" << TabFib(10) << "\n";
  return 0;
}
