/* RBTree, a self balancing binary search tree.
 * In the C++ STL, std::set (ordered) and std::map (ordered) are RBTrees.
 * unordered_map and unordered_set are hash tables of kv pairs or k
 * respectively.
 *
 * Key of invariants:
 * - root is black
 * - every node is either red or black
 * - all NIL nodes (leafs) are black
 * - a red node does not have a red child
 * - every path from a given node to its leaves goes through the same number of
 *   black nodes (in other words, we balance the tree on height)
 *
 */

// TODO: replace with cstdio.h
#include <iostream>

struct rb_node {
	int value;
	rb_node *left;
	rb_node *right;
	char color;  // 0 is black, 1 is red.
};
static constexpr rb_node kSentinel = rb_node{ 0, nullptr, nullptr, 0 };

struct rb_tree {
	rb_node *root;
};

/* Returns nullptr if not found, otherwise returns a pointer to a valid node
 * that holds the queried value.
 */
rb_node* search(rb_tree *tree, int value)
{
	if (!tree)
		return nullptr;
	// Look for where the node should be and return a pointer if its
	// properly there
	return nullptr;
};

/* If value already exists, returns pointer to the node.
 * Otherwise, inserts a value and returns newly inserted value.
 * Returns nullptr on invalid arguments.
 */
rb_node* add(rb_tree *tree, int value)
{
	if (!tree)
		return nullptr;
	rb_node* loc = search(tree, value);
	if (loc)
		return loc;
	loc = new rb_node {
		value,
		&kSentinel,
		&kSentinel,
		0,
	};
	// rebalance?
	return loc;
}

// Returns 1 if successfully removed entry, 0 if it was not found, -1 on
// invalid argument
int remove(rb_tree *tree, int value)
{
	if (!tree)
		return -1;
	rb_node* loc = search(tree, value);
	if (!loc)
		return 0;
	destroy(loc);
	// rebalance?
	return 1;
}

// rb_tree* deserialize(std::string_view s) { return nullptr; }
// std::string serialize(rb_tree *tree) { return ""; }

int main()
{
	if (search(nullptr, 0)) {
		std::cout << "search(nullptr, 0) got value, want nullptr\n";
		return -1;
	}
	rb_tree *t = new rb_tree;
	if (search(t, 0)) {
		std::cout << "search(t, 0) got value, want nullptr\n";
		return -1;
	}

	if (!add(t, 3)) {
		std::cout << "Failed add(t, 3)\n";
		return -1;
	}
	rb_node *root = search(t, 3);
	if (!(root && root->value == 3 && root->color == 0 &&
	      root->left == &kSentinel && root->right == &kSentinel)) {
		std::cout << "Root is not 3 with sentinel children\n";
		return -1;
	}

	if (!add(t, 1)) {
		std::cout << "Failed add(t, 1)\n";
		return -1;
	}
	if (!add(t, 4)) {
		std::cout << "Failed add(t, 4)\n";
		return -1;
	}
	rb_node *l = search(t, 1);
	if (root->left != l) {
		std::cout << "add(t, 1) did not place 1 as left child of 3\n";
		return -1;
	}
	rb_node *r = search(t, 4);
	if (root->right != r) {
		std::cout << "add(t, 4) did not place 4 as right child of 3\n";
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
