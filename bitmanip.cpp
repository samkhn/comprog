/* Demonstration of bit shifts
 * If you suspect that your integer type is longer than unsigned long, use 1ULL
 * instead of 1UL.
 */

#include <cstdio>

int main()
{
	// Sets bits with |1
	int one = 0 | (1UL << 0);
	printf("One: %d\n", one);

	// Clear a bit to 0 with &~1 or |0
	int clear = one & ~(1UL << 0);  // Clears the nth bit of one
	printf("Back to zero: %d\n", clear);

	int four = 0 | (1UL << 2);
	printf("Four: %d\n", four);

	/* Toggle bit with ^ aka XOR.
	 * XOR flag is high IFF bits have different truth values. */
	int five = four ^ (1UL << 0);
	printf("Five: %d\n", five);

	// Check a bit is set by shifting it to the right and &1
	for (int i = 3; i > 0; --i) {
		printf("In %d, bit %d is %d\n", 7, i, ((7 >> i) & 1UL));
	}

	// Flip a bit (regardless of initial value)
	int x = 0;

	/* NOTE: order of eval is (-x ^ thirteen) & (1UL << 3) get eval'd.
	 * Then thirteen is ^ with the intermediate result of prev computation.
	 */
	int thirteen = 13;  // 0b1101
	int bit_cleared = thirteen ^ (-x ^ thirteen) & (1UL << 3);
	printf("%d, after clearing bit %d is now %d\n",
		thirteen, 3, bit_cleared);
	x = 1;
	int bit_reset = bit_cleared ^ (-x ^ bit_cleared) & (1UL << 3);
	printf("%d, after resetting bit %d, is now %d\n",
		bit_cleared, 3, bit_reset);
	return 0;
}
