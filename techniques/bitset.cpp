// Bitsets and binary are a data structure too :o

#include <bitset>
#include <cassert>

int main() {
  std::bitset<4> a;
  constexpr std::bitset<4> initialized{0xA};
  std::bitset<4> b{"0011"};

  b |= 0b0100;
  assert(b == 0b0111);
  b &= 0b0011;
  assert(b == 0b0011);
  b ^= std::bitset<4>{0b1100};
  assert(b == 0b1111);

  b.reset();
  assert(b == 0);
  b.set();
  assert(b == 0b1111);
  assert(b.all() && b.any() && !b.none());
  b.flip();
  assert(b == 0);

  b.set(1, true);
  assert(b == 0b0010);
  b.set(1, false);
  assert(b == 0);
  b.flip(2);
  assert(b == 0b0100);
  b.reset(2);
  assert(b == 0);

  b[2] = true;
  assert(true == b[2]);

  assert(b.count() == 1);
  assert(b.size() == 4);
  assert(b.to_ullong() == 0b0100ULL);
  assert(b.to_string() == "0100");

  // If you suspect overflow on 1UL, use 1ULL.
  // Flip a bit (regardless of initial value)
  // NOTE: order of eval is (-x ^ thirteen) & (1UL << 3) get eval'd.
  // Then thirteen is ^ with the intermediate result of prev computation.
  int thirteen = 13;  // 0b1101
  int x;
  x = 0;
  int bit_cleared = thirteen ^ (-x ^ thirteen) & (1UL << 3);
  x = 1;
  int bit_reset = bit_cleared ^ (-x ^ bit_cleared) & (1UL << 3);
  assert(bit_reset == thirteen);
  assert(bit_cleared == 5);

  return 0;
}
