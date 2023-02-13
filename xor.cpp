// XOR is absurd
//
// XOR:
//   0 ^ 0 = 0
//   1 ^ 0 = 1
//   0 ^ 1 = 1
//   1 ^ 1 = 0
//
// Some properties:
//   x ^ 0 = 0 ^ x = x
//   x ^ x = 0
//   x ^ y = y ^ x
//
// The XOR trick:
// if we have a series of XOR operations a ^ b ^ c ...,
// then we can remove all pairs of duplicates without affecting results.
// a ^ b ^ c ^ b ^ a -> a ^ a ^ b ^ b ^ c = 0 ^ 0 ^ c = c.

#include <iostream>
#include <vector>

// Assumes the vector goes from 1 to n where n is a posint > 1.
int FindMissingValue(const std::vector<int>& container, int n) {
  int result = 0;
  for (int i = 1; i <= n; ++i)
    result ^= i;
  for (auto it = container.begin(); it != container.end(); ++it)
    result ^= *it;
  return result;
}

std::pair<int, int>
FindTwoMissingValues(const std::vector<int>& container, int n) {
  // missings represents u^v where u and v are the missing two values.
  // How do we pull them apart?
  // With xor, if a xor bit is 1, the bit in the args are different,
  // 0 if same. So if we look for the first bit in u^v with a 1, we know
  // that bit will be different in u and v.
  // We can then form two subarrays where in the first subarray, all values have the same bit set to 1 as u
  //  while in the second subarray all the values have the bit set to 0.
  int missings = FindMissingValue(container, n);
  int split_index_mask = missings & ~(missings - 1);
  int u = 0, v = 0;
  for (int i = 1; i <= n; ++i) {
    if (i & split_index_mask)
      u ^= i;
    else
      v ^= i;
  }
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (*it & split_index_mask)
      u ^= *it;
    else
      v ^= *it;
  }
  return std::make_pair(u, v);
}

int main() {
  // You can implement in-place swaps
  int a{10}, b{15};
  std::cout << "preswap. a: " << a << ". b: " << b << "\n";
  a ^= b;  // a contains a^b, b contains b.
  b ^= a;  // a contains a^b, b contains b^a^b->a.
  a ^= b;  // a contains a^b^a=b, b contains a.
  std::cout << "postswap. a: " << a << ". b: " << b << "\n";

  // Find the missing number
  // You are given an array A of n - 1 integers which are in the range
  // between 1 and n.
  // All numbers appear exactly once, except one number, which is missing.
  std::vector<int> sorted{1, 2, 3, 4, 6, 7};
  int sorted_n = 7, sorted_expect = 5;
  std::cout << "Sorted Test. "
    "Got: " << FindMissingValue(sorted, sorted_n) << ". "
    "Want: " << sorted_expect << "\n";
  std::vector<int> unsorted{4, 2, 1, 7, 6, 5};
  int unsorted_n = 7, unsorted_expect = 3;
  std::cout << "Unsorted Test. "
    "Got: " << FindMissingValue(unsorted, unsorted_n) << ". "
    "Want: " << unsorted_expect << "\n";

  // Find two missing values
  int missing_multiple_n = 7;
  std::vector<int> missing_multiple{1, 2, 5, 6, 7}; 
  std::pair<int, int> want{3, 4};
  std::pair<int, int> got =
    FindTwoMissingValues(missing_multiple, missing_multiple_n);
  std::cout << "Missing multiple. "
    "Got:{ " << got.first << ", " << got.second << " }. "
    "Want: { " << want.first << ", " << want.second << " }\n";

  // Can also be used to find duplicates and two duplicates but not more.
  
  return 0;
}
