#include <cstdio>

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

bool Exists(Tree *t, int value) {
  if (!t) {
    return false;
  }
  return (value == t->value) || Exists(t->left, value) ||
         Exists(t->right, value);
}

Tree *Insert(Tree *t, int value) {
  if (!t) {
    return new Tree{value, nullptr, nullptr};
  }
  if (value < t->value) {
    t->left = Insert(t->left, value);
  } else if (value > t->value) {
    t->right = Insert(t->right, value);
  }
  return t;
}

// TODO: cleanup this implementation
Tree *Delete(Tree *t, int value) {
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

Tree *generate_valid_tree() {
  return new Tree{5, new Tree{3, new Tree{2, nullptr, nullptr}, nullptr},
                  new Tree{6, nullptr, new Tree{10, nullptr, nullptr}}};
}

int main() {
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
  return 0;
}