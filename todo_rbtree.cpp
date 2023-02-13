/*
 * RBTree, a self balancing binary search tree.
 * In the C++ STL, std::set (ordered) and std::map (ordered) are RBTrees.
 * unordered_map and unordered_set are hash tables of kv pairs or k respectively.
 * 
 *
 * Key of invariants:
 * - root is black
 * - every node is either red or black
 * - all NIL nodes (leafs) are black
 * - a red node does not have a red child
 * - every path from a given node to its leaves goes through the same number of
 *    black nodes (in other words, we balance the tree on height)
 *
 */

#include <iostream>

struct RBNode {
	int value;
	RBNode *left;
	RBNode *right;
	char color;  // 0 is black, 1 is red.
};
static constexpr RBNode kSentinel = RBNode{ 0, nullptr, nullptr, 0 };

struct RBTree {
	RBNode *root;
};

// Returns nullptr if not found, otherwise returns a pointer to a valid node
// that holds the queried value.
RBNode* Search(RBTree *tree, int value) {
	if (!tree)
		return nullptr;
	// Look for where the node should be and return a pointer if its
	//  properly there
	return nullptr;
};

// If value already exists, returns pointer to the node.
// Otherwise, inserts a value and returns newly inserted value.
// Returns nullptr on invalid arguments.
RBNode* Add(RBTree *tree, int value) {
	if (!tree)
		return nullptr;
	RBNode* loc = Search(tree, value);
	if (loc)
		return loc;
	loc = new RBNode {
		.value{value},
		.left{&kSentinel},
		.right{&kSentinel},
		.char{0}
	};
	// rebalance?
}

// Returns 1 if successfully removed entry, 0 if it was not found, -1 on
// invalid argument
int Remove(RBTree *tree, int value) {
	if (!tree)
		return -1;
	RBNode* loc = Search(tree, value);
	if (!loc)
		return 0;
	destroy(loc);
	// rebalance?
	return 1;
}

// RBTree* Deserialize(std::string_view s) { return nullptr; }
// std::string Serialize(RBTree *t) { return ""; }

int main() {
	if (Search(nullptr, 0)) {
		std::cout << "Search(nullptr, 0) got value, want nullptr\n";
		return -1;
	}
	RBTree *t = new RBTree;
	if (Search(t, 0)) {
		std::cout << "Search(t, 0) got value, want nullptr\n";
		return -1;
	}

	if (!Add(t, 3)) {
		std::cout << "Failed Add(t, 3)\n";
		return -1;
	}
	RBNode *root = Search(t, 3);
	if (!(root && root->value == 3 && root->color == 0 &&
	      root->left == &kSentinel && root->right == &kSentinel)) {
		std::cout << "Root is not 3 with sentinel children\n";
		return -1;
	}

	if (!Add(t, 1)) {
		std::cout << "Failed Add(t, 1)\n";
		return -1;
	}
	if (!Add(t, 4)) {
		std::cout << "Failed Add(t, 4)\n";
		return -1;
	}
	RBNode *l = Search(t, 1);
	if (root->left != l) {
		std::cout << "Add(t, 1) did not place 1 as left child of 3\n";
		return -1;
	}
	RBNode *r = Search(t, 4);
	if (root->right != r) {
		std::cout << "Add(t, 4) did not place 4 as right child of 3\n";
		return -1;
	}
	// Search for them and assert their color and value
	// Insert a few elements (individual and initializer list)
	// Assert count of elements
	// Assert their color
	// Delete a few elements
	// Search and it should return null
	// Assert that the heights are what they should be
	//  (aka test key invariant of rbtree)

	// TODO: de/serialize
	// Serialize
	// Reconstruct the tree from serialize aka deserialize
	// Assert the two trees are the same
}
