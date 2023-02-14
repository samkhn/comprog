/* Binary search tree
 */

struct bst {
	int value;
	bst* left;
	bst* right;
};

// breadth first search and enforce that left is smaller than node and
// right is greater than node? is that the invariant?
int validate(bst *tree)
{
	return 0;
}

// bfs but keep a count of nodes we see
int count(bst *tree)
{
	return 0;
}

// multiple depth first searches but keep the max count?
int height(bst *tree)
{
	return 0;
}

// traverse, aligning with variant
bst* exists(bst *tree, int value)
{
	return nullptr;
}

// traverse but insert a new malloced node
bst* insert(bst *tree, int value)
{
	return nullptr;
}

// traverse but delete. rebalancing might be required
int remove(bst *tree, int value)
{
	return 0;
}

std::string inorder_traversal(bst *tree)
{
	return "";
}

std::string preorder_traversal(bst *tree)
{
	return "";
}

std::string postorder_traversal(bst *tree)
{
	return "";
}

std::string serialize(bst *tree)
{
	return "";
}

bst* deserialize(std::string ts)
{
	return nullptr;
}

int main()
{
	return 0;
}
