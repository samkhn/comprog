// Linked List

#include <initializer_list>
#include <iostream>
#include <string>


// FNode, or forward node, is the start of a singly linked list
struct FNode {
  int value;
  FNode *right;
};
static constexpr FNode kSentinelFNode = FNode{0, nullptr};


FNode* back(FNode *fl) {
  if (!fl->right) {
    return fl;
  }
  FNode *r = fl;
  while (fl) {
    r = fl;
    fl = fl->right;
  }
  return r;
}

FNode* Add(FNode *to, FNode *n) {
  if (!to) return n;
  back(to)->right = n;
  return n;
}

FNode* Add(FNode *to, int value) {
  return Add(to, new FNode {value, nullptr});
}

FNode* Add(FNode *to, std::initializer_list<int> values) {
  for (auto it = values.begin(); it != values.end(); it++) {
    to = Add(to, *it);
  }
  return to;
}

FNode* New(std::initializer_list<int> values) {
  if (values.begin() == values.end()) {
    return nullptr;
  }
  FNode *n = new FNode{0, nullptr};
  FNode *i = n;
  auto it = values.begin();
  n->value = *it++;
  for (; it != values.end(); it++) {
    i = Add(i, *it);
  }
  return n;
}

std::string Serialize(FNode *fl) {
  std::string s = "";
  while (fl) {
    s.append(std::to_string(fl->value));
    s.append(" ");
    fl = fl->right;
  }
  return s;
}

int Count(FNode *fl) {
  int c = 0;
  while (fl) {
    c++;
    fl = fl->right;
  }
  return c;
}

FNode* Merge(FNode *l, FNode *r) {
  if (!l) return r;
  if (!r) return l;
  FNode *lback = back(l);
  lback->right = r;
  return l;
}

FNode* Reverse(FNode *n) {
  FNode *f = n;
  FNode *b = back(n);
  FNode *start = f;
  int swap;
  if (f->right == b) {
    swap = f->value;
    f->value = f->right->value;
    f->right->value = swap;
    return f;
  }
  while (f != b) {
    // Swap values at front
    swap = f->value;
    f->value = f->right->value;
    f->right->value = swap;
    // Inserts newly swapped front 2 past node that b points to
    start = f->right->right;  // new starting point
    f->right->right = b->right;  // nodes we swapped not point to new sublist
    b->right = f;  // last element points to new start of sublist
    f = start;  // Go back to the start
  }
  return f;
}

bool HasCycle(FNode *n) {
  FNode *dn = n->right;
  while (dn) {
    if (dn) dn = dn->right;
    if (dn) dn = dn->right;
    if (n) n = n->right;
    if (n == dn) {
      return true;
    }
  }
  return false;
}


// Node is the start of a double linked list
// struct Node {
// 	int value;
// 	Node *left;
// 	Node *right;
// };
// static constexpr Node kSentinelNode = Node{0, nullptr, nullptr};
// Node* Add(Node *to, Node *n) {}
// Node* Add(Node *to, int value) {}
// Node* Add(Node *to, std::initializer_list<int> values) {}
// Node* New(std::initializer_list<int> values) {}
// std::string Serialize(Node *l) {}
// int Count(Node *l) {}
// Node* Merge(Node *l, Node *r) {}
// Node* Reverse(Node *n) {}
// bool HasCycle(Node *n) {}


int main() {
  // Single linked list test
  FNode *fl = New({});
  std::cout << "empty fl contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  
  fl = New({0});
  std::cout << "fl({0}) contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  
  fl = New({10, 2, 4, 14, -2});
  std::cout << "fl w/ real values contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  Add(fl, 11);
  Add(fl, {-1, -4});
  Add(fl, {});
  std::cout << "fl, after a bunch o'adds contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  
  fl = Add(nullptr, 0);
  std::cout << "Add(null, 0) generated list " << Count(fl) << " w/ nodes : { "
	    << Serialize(fl) << "}\n";

  FNode *o = New({14, 15});
  FNode *l = New({1, -23});
  fl = Merge(o, l);
  std::cout << "fl contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  fl = Merge(fl, New({}));
  std::cout << "fl merged with empty contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  fl = Merge(New({}), fl);
  std::cout << "empty merged w/ fl contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";

  fl = New({1, 2, 3, 4, 5, 6, 7});
  std::cout << "fl unreversed contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  fl = Reverse(fl);
  std::cout << "fl   reversed contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";
  
  fl = Reverse(New({11}));
  std::cout << "{11} reversed contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";

  fl = Reverse(New({0, 1}));
  std::cout << "{0, 1} reversed contains " << Count(fl) << " nodes : { "
	    << Serialize(fl) << "}\n";

  FNode *nocycle = New({1});
  std::cout << "Cycle in {1->null} ?: " << HasCycle(nocycle) << "\n";
  nocycle = New({1, 2, 3, 4});
  std::cout << "Cycle in {1->2->3->4->null} ?: " << HasCycle(nocycle) << "\n";
  FNode *cycle = nocycle;
  FNode *b = back(cycle);
  Add(b, cycle);  // Created a loop
  std::cout << "Cycle in {1->2->3->4->1}?: " << HasCycle(cycle) << "\n";

  return 0;
}
