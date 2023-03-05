// bited aka bit editing
// Demonstration of bitshifts and interesting bit operations
// If you suspect overflow on 1UL, use 1ULL.

#include <iostream>

int main() {
	// Flip a bit (regardless of initial value)
	// NOTE: order of eval is (-x ^ thirteen) & (1UL << 3) get eval'd.
	// Then thirteen is ^ with the intermediate result of prev computation.
	int x = 0;
	int thirteen = 13;  // 0b1101
	int bit_cleared = thirteen ^ (-x ^ thirteen) & (1UL << 3);
	
	x = 1;
	int bit_reset = bit_cleared ^ (-x ^ bit_cleared) & (1UL << 3);
	printf("%d, after resetting bit %d, is now %d\n", bit_cleared, 3, bit_reset);
	std::cout << thirteen << "(13), after clearing bit 3 is now " << bit_cleared
		<< " and switching back, we get " << bit_reset << "(13)\n";
	return 0;
}
