// Demonstration of transpose by rotating cycles within a matrix.

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// num_columns refers to the number of columns in the original matrix, not the
// desired column count post transpose.
void Transpose(int* begin, int* end, const std::size_t num_columns) {
  const int64_t size = (end - begin - 1);  // num_elements-1
  const int64_t num_rows = (end - begin) / num_columns;
  // TODO: if (num_row=num_col), just swap indices
  std::vector<bool> visited(end - begin);
  int* cycle = begin;
  while (++cycle != end) {
    if (visited[cycle - begin]) {
      continue;
    }
    int64_t i = cycle - begin;
    do {
      i = (i == size) ? size : (i * num_rows) % size;
      std::swap(*(begin + i), *cycle);
      visited[i] = true;
    } while ((begin + i) != cycle);
  }
}

int main() {
  int v[] = {0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "Pre transpose ";
  std::copy(v, v + 8, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  Transpose(v, v + 8, 4);
  std::cout << "Post transpose ";
  std::copy(v, v + 8, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  return 0;
}
