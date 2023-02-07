// Binary
// If you suspect that your integer type is longer than unsigned long, use 1ULL
// instead of 1UL.
#include <iostream>

int main() {
    int original{0};

    // Sets bits with |1
    int one = original | (1UL << 0);  
    std::cout << "one: " << one << "\n";

    // Clear a bit to 0 with &~1 or |0
    int clear = one & ~(1UL << 0);  // Clears the nth bit of one
    std::cout << "back to zero: " << clear << "\n";
  
    int four = original | (1UL << 2);
    std::cout << "four: " << four << "\n";

    // Toggle bit with ^ aka XOR.
    // XOR flag is high IFF bits have different truth values.
    int five = four ^ (1UL << 0);
    std::cout << "five: " << five << "\n";

    // Check a bit is set by shifting it to the right and &1
    int seven = 7;
    std::cout << "In 7, bit 3 is " << ((seven >> 3) & 1U)
	      << ", bit 2 is " << ((seven >> 2) & 1U)
	      << ", bit 1 is " << ((seven >> 1) & 1U)
	      << ", bit 0 is " << ((seven >> 0) & 1U) << ".\n";

    // Flip a bit (regardless of initial value)
    int x = 0;
  
    // NOTE: order of eval is (-x ^ thirteen) & (1UL << 3) get eval'd.
    // Then thirteen is ^ with the intermediate result of prev computation.
    int thirteen = 13;  // 0b1101
    int bit_cleared = thirteen ^ (-x ^ thirteen) & (1UL << 3);
    std::cout << "13, after clearing bit 3, is now 5: "
	      << bit_cleared << "\n";
    x = 1;
    int bit_reset = bit_cleared ^ (-x ^ bit_cleared) & (1UL << 3);
    std::cout << "5, after resetting bit 3, is now 13: "
	      << bit_reset << "\n";
    return 0;
}
