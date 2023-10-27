// Binary Search Tree
// Invariant: left node is smaller than current, right node is larger.

#include <cstdio>
#include <sstream>
#include <string>

struct Tree {
  int value;
  Tree *left;
  Tree *right;
};

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

Tree *deserialize(std::istringstream &s) {
  std::string v;
  s >> v;
  if (v == kDelimiter) {
    return nullptr;
  }
  return new Tree{std::stoi(v), deserialize(s), deserialize(s)};
}

Tree *Deserialize(std::string &s) {
  std::istringstream in(s);
  return deserialize(in);
}

// Test cases

Tree *generate_invalid_tree() {
  return new Tree{5, new Tree{3, nullptr, nullptr},
                  new Tree{6, new Tree{2, nullptr, nullptr},
                           new Tree{10, nullptr, nullptr}}};
}

Tree *generate_valid_tree() {
  return new Tree{5, new Tree{3, new Tree{2, nullptr, nullptr}, nullptr},
                  new Tree{6, nullptr, new Tree{10, nullptr, nullptr}}};
}

int main() {
  Tree *nt = generate_invalid_tree(), *t = generate_valid_tree();
  printf("Pr (invalid): %s\n", ToString(nt, Traversal::PreOrder).c_str());
  printf("In (invalid): %s\n", ToString(nt, Traversal::InOrder).c_str());
  printf("Po (invalid): %s\n", ToString(nt, Traversal::PostOrder).c_str());
  printf("Pr (valid): %s\n", ToString(t, Traversal::PreOrder).c_str());
  printf("In (valid): %s\n", ToString(t, Traversal::InOrder).c_str());
  printf("Po (valid): %s\n", ToString(t, Traversal::PostOrder).c_str());
  std::string serialized_t = Serialize(t);
  printf("Serialized tree: %s\n", serialized_t.c_str());
  Tree *dt = Deserialize(serialized_t);
  printf("Deseralized tree preorder traversal: %s\n",
         ToString(t, Traversal::PreOrder).c_str());
  return 0;
}
