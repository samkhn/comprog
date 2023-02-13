// Tail recursion
// Guarentees a bound on the number of stack frames needed to compute recursion

#include <iostream>
#include <stdint.h>

// Note: I tried to add this inline assembly to find the fp address
//  uintptr_t fp;
//  __asm mov fp, esp;
//  std::cout << "factorial(" << x << ") framepointer: "
//            << fp << "\n";
// Upon inspecting the disassembly in godbolt, turns out the inline assembly
// impacts the optimization. Just ended up using godbolt.


int nontr_factorial(int x) {
	if (x == 1)
		return 1;
	return x*nontr_factorial(x-1);
}


int factorial(int x, int sum) {
	if (x == 1)
		return sum;
	return factorial(x-1, sum*x);
}


int main(){
	std::cout << "Non tail recursive factorial of 5 = "
		  << nontr_factorial(5) << "\n"
		  << "Tail recursive factorial of 5 = "
		  << factorial(5, 1) << "\n";
	return 0;
}
