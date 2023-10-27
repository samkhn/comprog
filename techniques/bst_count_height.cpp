#include <algorithm>
#include <cstdio>

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

int Count(Tree *t) {
  if (!t) {
    return 0;
  }
  return 1 + Count(t->left) + Count(t->right);
}

int Height(Tree *t) {
  if (!t) {
    return 0;
  }
  return 1 + std::max(Height(t->left), Height(t->right));
}

// Tests

Tree *generate_single_node() { return new Tree{1, nullptr, nullptr}; }

Tree *generate_left_child_only() {
  return new Tree{1, new Tree{2, nullptr, nullptr}, nullptr};
}
static const int left_child_only_count = 2;
static const int left_child_only_height = 2;

Tree *generate_right_child_only() {
  return new Tree{1, nullptr, new Tree{2, nullptr, nullptr}};
}
static const int right_child_only_count = 2;
static const int right_child_only_height = 2;

Tree *generate_invalid_tree() {
  return new Tree{5, new Tree{3, nullptr, nullptr},
                  new Tree{6, new Tree{2, nullptr, nullptr},
                           new Tree{10, nullptr, nullptr}}};
}
static const int invalid_count = 5;
static const int invalid_height = 3;

Tree *generate_valid_tree() {
  return new Tree{5, new Tree{3, new Tree{2, nullptr, nullptr}, nullptr},
                  new Tree{6, nullptr, new Tree{10, nullptr, nullptr}}};
}
static const int valid_count = 5;
static const int valid_height = 3;

int main() {
  int c = 0;
  if (Count(nullptr)) {
    printf("Count(null_tree) returned a value\n");
  }
  c = Count(generate_single_node());
  if (c != 1) {
    printf("Count(single_node) = %d. Want %d\n", c, 1);
  }
  c = Count(generate_left_child_only());
  if (c != left_child_only_count) {
    printf("Count(left_child_only) = %d. Want %d\n", c, left_child_only_count);
  }
  c = Count(generate_right_child_only());
  if (c != right_child_only_count) {
    printf("Count(right_child_only) = %d. Want %d\n", c,
           right_child_only_count);
  }
  c = Count(generate_valid_tree());
  if (c != valid_count) {
    printf("Count(valid) = %d. Want %d\n", c, valid_count);
  }
  c = Count(generate_invalid_tree());
  if (c != invalid_count) {
    printf("Count(invalid) = %d. Want %d\n", c, invalid_count);
  }
  int h = 0;
  h = Height(generate_valid_tree());
  if (h != valid_height) {
    printf("Height(valid) = %d. Want %d\n", h, valid_height);
  }
  h = Height(generate_invalid_tree());
  if (h != invalid_height) {
    printf("Height(invalid) = %d. Want %d\n", h, invalid_height);
  }
  return 0;
}