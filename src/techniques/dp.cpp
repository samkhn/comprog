// Dynamic programming

#include <iostream>
#include <unordered_map>

int dumb_fib(int n) {
  if (!n || n == 1) {
    return n;
  }
  return dumb_fib(n - 1) + dumb_fib(n - 2);
}

inline const std::unordered_map<int, int> kMemo = {{0, 0}, {1, 1}};

int memo_fib(std::unordered_map<int, int> &m, int n) {
  auto it = m.find(n);
  if (it != m.end()) {
    return it->second;
  }
  m[n] = memo_fib(m, n - 1) + memo_fib(m, n - 2);
  return m[n];
}

int main() {
  std::cout << "dumb_fib(10)=" << dumb_fib(10) << "\n";
  std::unordered_map memo = kMemo;
  std::cout << "memo_fib(10)=" << memo_fib(memo, 10) << "\n";
  return 0;
}
