/* Two heaps.
 * Inspiration: https://emre.me/coding-patterns/two-heaps/
 *
 * You can find the median of numbers by maintaining two heaps (a max+min).
 * Other problems might ask you to use a max+max or min+min heap.
 *
 */

#include <functional>
#include <queue>
#include <string>
#include <vector>

struct result {
	int status;  // 1 if fine, 0 if not.
	float value;
};
std::string print(const result &r) {
	std::string s;
	s.append(std::to_string(r.status));
	s.append(" ");
	s.append(std::to_string(r.value));
	s.append(" ");
	return s;
}

typedef std::priority_queue<int, std::vector<int>, std::less<int>> max_q;
typedef std::priority_queue<int, std::vector<int>, std::greater<int>> min_q;
struct list {
	int c;
	max_q left_side_queue;
	min_q right_side_queue;
};

list *new_list();
int insert(list *l, int v);
result median(list *l);

result _left_top(list *l);
result _right_top(list *l);

list *new_list() {
	list *l = new list;
	l->c = 0;
	return l;
}

int insert(list *l, int v) {
	if (!l) return -1;
	result m = median(l);
	if (!m.status) return -1;
	if (m.value == 0 || v <= m.value) {
		l->left_side_queue.push(v);
		result left = _left_top(l);
		if (!left.status) return -1;
		if (v < left.value) {
			l->right_side_queue.push(left.value);
			l->left_side_queue.pop();
		}
	} else {
		l->right_side_queue.push(v);
		result right = _right_top(l);
		if (!right.status) return -1;
		if (v > right.value) {
			l->left_side_queue.push(right.value);
			l->right_side_queue.pop();
		}
	}
	l->c++;
	return 1;
}

result _left_top(list *l) {
	if (!l) return result{0, 0};
	if (l->left_side_queue.empty()) return result{1, 0};
	return result{1, (float)l->left_side_queue.top()};
}

result _right_top(list *l) {
	if (!l) return result{0, 0};
	if (l->right_side_queue.empty()) return result{1, 0};
	return result{1, (float)l->right_side_queue.top()};
}

result median(list *l) {
	if (!l) return result{0, 0};
	if (l->c == 0) return result{1, 0};
	result left_top_result = _left_top(l);
	if (!left_top_result.status) return result{0, 0};
	result right_top_result = _right_top(l);
	if (!right_top_result.status) return result{0, 0};
	if (l->c % 2) {
		return left_top_result;
	}
	return result{1, ((left_top_result.value + right_top_result.value) / 2)};
}

int main() {
	list *l = new_list();

	result s = median(l);
	if (s.value != 0) {
		printf("median({}). Got %s. Want { 1 0 }\ngot.count %d\n", print(s).c_str(), l->c);
		return -1;
	}

	if (!insert(l, 3)) {
		printf("insert({}, 3) got fail, want success\n");
		return -1;
	}

	s = median(l);
	if (s.value != 3) {
		printf("median({3}). Got %s. Want { 1 3 }\ngot.count %d\n", print(s).c_str(), l->c);
		return -1;
	}

	if (!insert(l, 1)) {
		printf("insert({3}, 1) got fail, want success\n");
		return -1;
	}

	s = median(l);
	if (s.value != 2) {
		printf("median({1, 3}). Got %s. Want { 1 2 }\ngot.count %d\n", print(s).c_str(), l->c);
		return -1;
	}
	return 0;
}
