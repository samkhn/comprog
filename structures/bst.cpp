// Binary Search Tree
// Invariant: left node is smaller than current, right node is larger.

#include <algorithm>
#include <cstdio>
#include <sstream>
#include <string>

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

// Uses in in-order traversal of the tree.
// Sets isValid, initialized true, to false.
// During an in-order traversal we could have added each elements we visited to
// a linked list and then checked that the linked list is in increasing order.
// Instead, we have prev point to what element we would have added to the list
// and compare root (what we are validating now) to prev.
void validate(Tree *root, Tree *prev, bool *is_valid) {
  if (!root) {
    return;
  }
  validate(root->left, prev, is_valid);
  if (prev && prev->value >= root->value) {
    *is_valid = false;
    return;
  }
  prev = root;
  validate(root->right, prev, is_valid);
}

bool IsValid(Tree *t) {
  if (!t) {
    return false;
  }
  bool is_valid = true;
  Tree prev;
  validate(t, &prev, &is_valid);
  return is_valid;
}

int Count(Tree *t) {
  if (!t) {
    return 0;
  }
  return 1+Count(t->left)+Count(t->right);
}

int Height(Tree *t) {
  if (!t) {
    return 0;
  }
  return 1+std::max(Height(t->left), Height(t->right));
}

bool Exists(Tree *t, int value) {
  if (!t) {
    return false;
  }
  return (value == t->value)
      || Exists(t->left, value) || Exists(t->right, value);
}

Tree* Insert(Tree *t, int value) {
  if (!t) {
    return new Tree{ value, nullptr, nullptr };
  }
  if (value < t->value) {
    t->left = Insert(t->left, value);
  } else if (value > t->value) {
    t->right = Insert(t->right, value);
  }
  return t;
}

Tree* Delete(Tree *t, int value) {
  if (!t) {
    return nullptr;
  }
  if (value < t->value) {
    t->left = Delete(t->left, value);
    return t->left;
  } else if (value > t->value) {
    t->right = Delete(t->right, value);
    return t->right;
  } else if (value == t->value) {
    if (!t->left && !t->right) {
      delete t;
      return nullptr;
    } else if (t->left && !t->right) {
      t->value = t->left->value;
      t->left = t->left->left;
      t->right = t->left->right;
      delete t->left;
      return t;
    } else if (!t->left && t->right) {
      t->value = t->right->value;
      t->left = t->right->left;
      t->right = t->right->right;
      delete t->right;
      return t;
    } else {
      Tree *new_root = t->right;
      while (new_root && new_root->left) {
        new_root = new_root->left;
      }
      t->value = new_root->value;
      t->right = Delete(t->right, t->value);
      return t->right;
    }
  }
  return nullptr;
}

enum class Traversal { PreOrder, PostOrder, InOrder };

void inOrderTreeToString(Tree *t, std::string *to) {
  if (!t || !to) {
    return;
  }
  inOrderTreeToString(t->left, to);
  to->append(std::to_string(t->value));
  to->append(" ");
  inOrderTreeToString(t->right, to);
}

void preOrderTreeToString(Tree *t, std::string *to) {
  if (!t || !to) {
    return;
  }
  to->append(std::to_string(t->value));
  to->append(" ");
  preOrderTreeToString(t->left, to);
  preOrderTreeToString(t->right, to);
}

void postOrderTreeToString(Tree *t, std::string *to) {
  if (!t || !to) {
    return;
  }
  postOrderTreeToString(t->left, to);
  postOrderTreeToString(t->right, to);
  to->append(std::to_string(t->value));
  to->append(" ");
}

std::string ToString(Tree *t, Traversal order) {
  std::string s = "";
  if (!t) {
    return s;
  }
  switch (order) {
    case Traversal::InOrder:
      inOrderTreeToString(t, &s);
      break;
    case Traversal::PreOrder:
      preOrderTreeToString(t, &s);
      break;
    case Traversal::PostOrder:
      postOrderTreeToString(t, &s);
      break;
  }
  return s;
}

static constexpr std::string_view kDelimiter = "*";

void serialize(Tree *t, std::string *s) {
  if (!s) {
    return;
  }
  if (!t) {
    s->append(kDelimiter);
    s->append(" ");
    return;
  }
  s->append(std::to_string(t->value));
  s->append(" ");
  serialize(t->left, s);
  serialize(t->right, s);
}

std::string Serialize(Tree *t) {
  std::string s = "";
  if (!t) {
    return s;
  }
  serialize(t, &s);
  return s;
}

Tree* deserialize(std::istringstream &s) {
  std::string v;
  s >> v;
  if (v == kDelimiter) {
    return nullptr;
  }
  return new Tree { std::stoi(v),
    deserialize(s),
    deserialize(s)
  };
}

Tree* Deserialize(std::string &s) {
  std::istringstream in(s);
  return deserialize(in);
}


// Test cases

Tree* generate_single_node() {
  return new Tree {1, nullptr, nullptr };
}

Tree* generate_left_child_only() {
  return new Tree {1, new Tree{ 2, nullptr, nullptr }, nullptr };
}
static const int left_child_only_count = 2;
static const int left_child_only_height = 2;

Tree* generate_right_child_only() {
  return new Tree {1, nullptr, new Tree{ 2, nullptr, nullptr } };
}
static const int right_child_only_count = 2;
static const int right_child_only_height = 2;

Tree* generate_invalid_tree() {
  return new Tree { 5,
    new Tree{ 3, nullptr, nullptr },
    new Tree{ 6,
      new Tree { 2, nullptr, nullptr },
      new Tree { 10, nullptr, nullptr }
    }
  };
}
static const int invalid_count = 5;
static const int invalid_height = 3;

Tree* generate_valid_tree() {
  return new Tree { 5,
    new Tree{ 3, new Tree { 2, nullptr, nullptr }, nullptr },
    new Tree{ 6, nullptr, new Tree { 10, nullptr, nullptr } }
  };
}
static const int valid_count = 5;
static const int valid_height = 3;

int main() {  
  // Count tree nodes
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
    printf("Count(right_child_only) = %d. Want %d\n", c, right_child_only_count);
  }
  c = Count(generate_valid_tree());
  if (c != valid_count) {
    printf("Count(valid) = %d. Want %d\n", c, valid_count);
  }
  c = Count(generate_invalid_tree());
  if (c != invalid_count) {
    printf("Count(invalid) = %d. Want %d\n", c, invalid_count);
  }

  // Height of tree
  int h = 0;
  h = Height(generate_valid_tree());
  if (h != valid_height) {
    printf("Height(valid) = %d. Want %d\n", h, valid_height);
  }
  h = Height(generate_invalid_tree());
  if (h != invalid_height) {
    printf("Height(invalid) = %d. Want %d\n", h, invalid_height);
  }
  
  // Validate tree
  if (!IsValid(generate_valid_tree())) {
    printf("Valid tree called invalid\n");
  }  
  if (IsValid(generate_invalid_tree())) {
    printf("Invalid tree called valid\n");
  }

  // Insert, Exist, Delete
  Tree *t = nullptr;
  if (Exists(t, 1)) {
    printf("Exist(nullptr, 1) got something when it shouldn't have\n");
  }
  if (Delete(t, 1)) {
    printf("Delete(nullptr, 1) got soemthing when it shouldn't have\n");
  }
  t = Insert(t, 1);
  if (!Exists(t, 1)) {
    printf("Exist(t, 1) didn't find 1\n");
  }
  t = Insert(t, -1);
  t = Insert(t, 0);

  t = generate_valid_tree();
  if (!Exists(t, 5)) {
    printf("Exist(valid, 5) could not find 5 when it exists\n");
  }
  printf("Pr: %s\n", ToString(t, Traversal::PreOrder).c_str());
  printf("In: %s\n", ToString(t, Traversal::InOrder).c_str());
  printf("Po: %s\n", ToString(t, Traversal::PostOrder).c_str());
  Delete(t, 5);
  if (Exists(t, 5)) {
    printf("Exist(valid, 5) could found 5 when it shouldn't have\n");
  }
  printf("Del(5). Pr: %s\n", ToString(t, Traversal::PreOrder).c_str());
  printf("Del(5). In: %s\n", ToString(t, Traversal::InOrder).c_str());
  printf("Del(5). Po: %s\n", ToString(t, Traversal::PostOrder).c_str());

  t = generate_valid_tree();
  std::string serialized_t = Serialize(t);
  printf("Serialized tree: %s\n", serialized_t.c_str());
  Tree *dt = Deserialize(serialized_t);
  printf("Deseralized tree preorder traversal: %s\n",
         ToString(t, Traversal::PreOrder).c_str());
  if (Count(t) != Count(dt)) {
    printf("Count(original) != Count(deserialized)\n");
  }
  if (Height(t) != Height(dt)) {
    printf("Height(original) != Height(deserialized)\n");
  }
  return 0;
}
