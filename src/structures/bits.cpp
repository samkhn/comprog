// Bitsets and binary are a data structure too :o

#include <bitset>
#include <cassert>
#include <iostream>

int main() {
	std::bitset<4> a;
	constexpr std::bitset<4> initialized{0xA};
	std::bitset<4> b{"0011"};
	
	b |= 0b0100; assert(b == 0b0111);
	b &= 0b0011; assert(b == 0b0011);
	b ^= std::bitset<4>{0b1100}; assert(b == 0b1111);
	
	b.reset(); assert(b == 0);
	b.set(); assert(b == 0b1111);
	assert(b.all() && b.any() && !b.none());
	b.flip(); assert(b == 0);
	
	b.set(1, true); assert(b == 0b0010);
	b.set(1, false); assert(b == 0);
	b.flip(2); assert(b == 0b0100);
	b.reset(2); assert(b == 0);
	
	b[2] = true; assert(true == b[2]);
	
	assert(b.count() == 1);
	assert(b.size() == 4);
	assert(b.to_ullong() == 0b0100ULL);
	assert(b.to_string() == "0100");
	
	return 0;
}
