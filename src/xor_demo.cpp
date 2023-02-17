// XOR is absurd

// XOR:
//   0 ^ 0 = 0
//   1 ^ 0 = 1
//   0 ^ 1 = 1
//   1 ^ 1 = 0

// Some properties:
//   x ^ 0 = 0 ^ x = x
//   x ^ x = 0
//   x ^ y = y ^ x

// The XOR trick:
//  if we have a series of XOR operations a ^ b ^ c ...,
//  then we can remove all pairs of duplicates without affecting results.
//  a ^ b ^ c ^ b ^ a -> a ^ a ^ b ^ b ^ c = 0 ^ 0 ^ c = c.


#include <vector>

// Find the missing number
// You are given an array A of n - 1 integers which are in the range
// between 1 and n. All numbers appear exactly once, except one number,
// which is missing.
// Assumes the vector goes from 1 to n where n is a posint > 1.
int find_missing(const std::vector<int>& container, int n) {
  int result = 0;
  for (int i = 1; i <= n; ++i) result ^= i;
  for (auto it = container.begin(); it != container.end(); ++it) result ^= *it;
  return result;
}

// Finding two missing values is a bit trickier
// (int) missings represents u^v where u and v are the missing two values.
// How do we pull them apart?
//  With xor, if a xor bit is 1, the bit in the args are different,
//  0 if same. So if we look for the first bit in u^v with a 1, we know
//  that bit will be different in u and v.
// We can then form two subarrays where in the first subarray, all values have
//  the same bit set to 1 as u while in the second subarray all the values have
//  the bit set to 0.
std::pair<int, int> find_two_missing(const std::vector<int>& container, int n) {
  int missings = find_missing(container, n);
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

  int a = 10;
  int b = 15;
  printf("Pre  swap. a: %d. b: %d\n", a, b);
  a ^= b;
  b ^= a;
  a ^= b;
  printf("Post swap. a: %d. b: %d\n", a, b);

  // Find one missing value

  std::vector<int> sorted{1, 2, 3, 4, 6, 7};
  int sorted_n = 7;
  printf("Sorted test. Got %d. Want %d\n", find_missing(sorted, sorted_n), 5);

  std::vector<int> unsorted{4, 2, 1, 7, 6, 5};
  int unsorted_n = 7;
  printf("Unsorted test. Got %d. Want %d\n", find_missing(unsorted, unsorted_n),
         3);

  // Find two missing values

  int missing_multiple_n = 7;
  std::vector<int> missing_multiple{1, 2, 5, 6, 7};
  std::pair<int, int> got =
      find_two_missing(missing_multiple, missing_multiple_n);
  printf("find_two_missing(m, 7). Got {%d, %d}. Want {%d, %d}\n", got.first,
         got.second, 3, 4);

  // Can also be used to find duplicates and two duplicates but not more.

  return 0;
}
