// Heaps aka Priority Queues
// Good for finding nth largest/smallest element in an array.

#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <vector>

// In the STL: diff of std::less vs std::greater?
// std::less<int> (default std:pq) pushes smaller elements to earlier indices
// of the underlying contiguous container (lhs < rhs). std::greater (where
// lhs > rhs) pushes larger elements to the earlier indices of the underlying
// container.
bool Lesser(int l, int r) { return l < r; }
bool Greater(int l, int r) { return l > r; }

class BinaryHeap {
	// complete binary tree starting at index 0
	std::vector<int> data_;
	std::function<bool(int, int)> comp_;

	void fixUp(int i) {
		while (i > 0 && comp_(data_[i / 2], data_[i])) {
			std::swap(data_[i / 2], data_[i]);
			i /= 2;
		}
	}

	void fixDown(int i) {
		std::size_t last = Size() - 1;
		while (2 * i + 1 <= last) {
			int c = 2 * i + 1;
			if (c < last && comp_(data_[c], data_[c + 1])) {
				c++;
			}
			if (!comp_(data_[i], data_[c])) {
				break;
			}
			std::swap(data_[i], data_[c]);
			i = c;
		}
	}

public:
	BinaryHeap() { comp_ = Lesser; }
	BinaryHeap(std::function<bool(int, int)> comp) : comp_(comp) {}

	bool Empty() const { return data_.empty(); }
	std::size_t Size() const { return data_.size(); }
	int Top() const { return data_[0]; }

	void Push(int v) {
		data_.push_back(v);
		fixUp(data_.size() - 1);
	}

	void Pop() {
		data_[0] = data_.back();
		data_.pop_back();
		fixDown(0);
	}

	std::string ToString() const {
		std::string s = "";
		if (Empty()) {
			return s;
		}
		s.append(std::to_string(data_[0]));
		for (int i = 1; i < data_.size(); ++i) {
			s.append(" ");
			s.append(std::to_string(data_[i]));
		}
		return s;
	}
};

// q is passed by value because there is no way to traverse the PQ without
// modifying the original.
template <typename Q> std::string ToString(Q q) {
	std::string s = "";
	s.append(std::to_string(q.top()));
	q.pop();
	while (!q.empty()) {
		s.append(" ");
		s.append(std::to_string(q.top()));
		q.pop();
	}
	return s;
}

int NthLargestItem(const std::vector<int> &v, int n) {
	std::priority_queue<int> q(v.begin(), v.end());
	while (--n) {
		q.pop();
	}
	return q.top();
}

int main() {
	std::vector<int> v{1, 5, 12, 4};
	std::priority_queue<int> maxq(v.begin(), v.end());
	std::priority_queue<int, std::vector<int>, std::greater<int>> minq(v.begin(), v.end());

	std::cout << "\nv: ";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
	std::cout << "1st largest item in v is " << NthLargestItem(v, 1) << "\n";
	std::cout << "2nd largest item in v is " << NthLargestItem(v, 2) << "\n";
	std::cout << "3rd largest item in v is " << NthLargestItem(v, 3) << "\n\n";
	std::cout << "maxq (default)(std::less<int>): " << ToString(maxq) << "\n";
	std::cout << "minq (std::greater<int>): " << ToString(minq) << "\n";

	BinaryHeap h; // default aka h(Lesser);
	h.Push(1);
	std::cout << "BinaryMaxHeap({1}). Top is " << h.Top() << "\n";
	h.Push(5);
	std::cout << "Post Push(5), Top is " << h.Top() << "\n";
	h.Push(12);
	std::cout << "Post Push(12), Top is " << h.Top() << "\n";
	h.Push(4);
	std::cout << "Post Push(4), Top is " << h.Top() << "\n";
	h.Pop();
	std::cout << "Post Pop(), Top is " << h.Top() << "\n\n";

	BinaryHeap mh(Greater);
	mh.Push(1);
	std::cout << "BinaryMinHeap({1}). Top is " << mh.Top() << "\n";
	mh.Push(5);
	std::cout << "Post Push(5), Top is " << mh.Top() << "\n";
	mh.Push(12);
	std::cout << "Post Push(12), Top is " << mh.Top() << "\n";
	mh.Push(4);
	std::cout << "Post Push(4), Top is " << mh.Top() << "\n";
	mh.Pop();
	std::cout << "Post Pop(), Top is " << mh.Top() << "\n\n";

	return 0;
}
