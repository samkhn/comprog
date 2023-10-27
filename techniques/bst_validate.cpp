// Uses in in-order traversal of the tree.
// Sets isValid, initialized true, to false.
// During an in-order traversal we could have added each elements we visited to
// a linked list and then checked that the linked list is in increasing order.
// Instead, we have prev point to what element we would have added to the list
// and compare root (what we are validating now) to prev.

#include <cstdio>

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

void validate(Tree *root, Tree *prev, bool *is_valid) {
  if (!root) return;
  validate(root->left, prev, is_valid);
  if (prev && prev->value >= root->value) {
    *is_valid = false;
    return;
  }
  prev = root;
  validate(root->right, prev, is_valid);
}

bool IsValid(Tree *t) {
  bool is_valid = true;
  Tree prev{0, nullptr, nullptr};
  validate(t, &prev, &is_valid);
  return is_valid;
}

Tree *generate_valid_tree() {
  return new Tree{5, new Tree{3, new Tree{2, nullptr, nullptr}, nullptr},
                  new Tree{6, nullptr, new Tree{10, nullptr, nullptr}}};
}

Tree *generate_invalid_tree() {
  return new Tree{5, new Tree{3, nullptr, nullptr},
                  new Tree{6, new Tree{2, nullptr, nullptr},
                           new Tree{10, nullptr, nullptr}}};
}

int main() {
  if (!IsValid(generate_valid_tree())) {
    printf("Valid tree called invalid\n");
  }
  if (IsValid(generate_invalid_tree())) {
    printf("Invalid tree called valid\n");
  }
  return 0;
}
