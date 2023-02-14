/* Monotonic stack
 * Stack where values have some monotonic invariant
 * e.g. strictly increasing (1, 4, 5) or non-decreasing (1, 4, 4, 5)
 or strictly decreasing (5, 4, 1) or non-increasing (5, 4, 4, 1).
 * Usually good for questions that ask for the next largest/smallest element or
 *   previous largest/smallest element.
 * Time and space complexity is usually O(n)...ish
 */

#include <vector>

std::vector<int> next_greater(std::vector<int> values)
{
	std::vector<int> stack;
	std::vector<int> ng(values.size(), -1);
	/* keep adding indices (i) to the stack until you encounter a value
	 * greater than the top of the stack. when you encounter a value at i
	 * greater than the top of the stack, you have found the next greater
	 * element at i. the next greater index for the index at the top of the
	 * stack is i.
	 */
	for (int i = 0; i < values.size(); i++) {
		while (stack.size() && values[i] > values[stack.back()]) {
			ng[stack.back()] = i;
			stack.pop_back();
		}
		stack.push_back(i);
	}
	return ng;
}

std::vector<int> previous_greater(std::vector<int> values)
{
	std::vector<int> stack;
	std::vector<int> pg(values.size(), -1);
	for (int i = 0; i < values.size(); i++) {
		while (stack.size() && values[i] >= values[stack.back()])
			stack.pop_back();
		if (stack.size())
			pg[i] = stack.back();
		stack.push_back(i);
	}
	return pg;
}

// Next smaller element looks like next greater
//   you keep adding indices to the stack until you encounter a value at (i) that is smaller than the top,
//   the next smaller value from the index at the top of the stack is i
// Previous smaller element looks like previous greater

int main()
{
	std::vector<int> a{13, 8, 1, 5, 2, 5, 9, 7, 6, 12};
	std::vector<int> ng = next_greater(a);
	std::vector<int> pg = previous_greater(a);
	printf("For\n{ ");
	for (int v : a)
		printf("%d ", v);
	printf("}. Next greater is\n{ ");
	for (int v : ng)
		printf("%d ", v);
	printf("}. Prev greater is\n{ ");
	for (int v : pg)
		printf("%d ", v);
	printf("}\n");
	return 0;
}
