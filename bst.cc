// Binary search tree

#include <format>
#include <iostream>

struct BST {
  int value;
  BST* left;
  BST* right;
};

// breadth first search and enforce that left is smaller than node and
// right is greater than node? is that the invariant?
int Validate(BST *tree) {
  return 0;
}

// bfs but keep a count of nodes we see
int Count(BST *tree) {  
  return 0;
}

// multiple depth first searches but keep the max count?
int Height(BST *tree) {
  return 0;
}

// traverse, aligning with variant
BST* Exists(BST *tree, int value) {
  return nullptr;
}

// traverse but insert a new malloced node
BST* Insert(BST *tree, int value) {  
  return nullptr;
}

// traverse but delete. rebalancing might be required
int Delete(BST *tree, int value) {
  return 0;
}

std::string InOrderTraversalToStr(BST *tree) {
  return "";
}

std::string PreOrderTraversalToStr(BST *tree) {
  return "";
}

std::string PostOrderTraversalToStr(BST *tree) {
  return "";
}

void Serialize(BST *tree, std::ostream os) {}

BST* Deserialize(std::istream is) { return nullptr; }

int main() {
  return 0;
}
