#include "include/list.hpp"

ForwardList *Back(ForwardList *fl) {
  if (!fl->right) return fl;
  ForwardList *r = fl;
  while (fl) {
    r = fl;
    fl = fl->right;
  }
  return r;
}

ForwardList *Add(ForwardList *to, ForwardList *n) {
  if (!to) return n;
  Back(to)->right = n;
  return n;
}

ForwardList *Add(ForwardList *to, int value) {
  return Add(to, new ForwardList{value, nullptr});
}

ForwardList *Add(ForwardList *to, std::initializer_list<int> values) {
  for (auto it = values.begin(); it != values.end(); it++) to = Add(to, *it);
  return to;
}

ForwardList *NewForwardList(std::initializer_list<int> values) {
  if (values.begin() == values.end()) return nullptr;
  ForwardList *n = new ForwardList{0, nullptr};
  ForwardList *i = n;
  auto it = values.begin();
  n->value = *it++;
  for (; it != values.end(); it++) i = Add(i, *it);
  return n;
}

std::string Serialize(ForwardList *fl) {
  std::string s = "";
  while (fl) {
    s.append(std::to_string(fl->value));
    s.append(" ");
    fl = fl->right;
  }
  return s;
}

int Count(ForwardList *fl) {
  int c = 0;
  while (fl) {
    c++;
    fl = fl->right;
  }
  return c;
}

ForwardList *Merge(ForwardList *l, ForwardList *r) {
  if (!l) return r;
  if (!r) return l;
  Back(l)->right = r;
  return l;
}

ForwardList *Reverse(ForwardList *n) {
  ForwardList *f = n;
  ForwardList *b = Back(n);
  ForwardList *start = f;
  int swap;
  if (f->right == b) {
    swap = f->value;
    f->value = f->right->value;
    f->right->value = swap;
    return f;
  }
  while (f != b) {
    swap = f->value;
    f->value = f->right->value;
    f->right->value = swap;
    start = f->right->right;
    f->right->right = b->right;
    b->right = f;
    f = start;
  }
  return f;
}

bool HasCycle(ForwardList *n) {
  ForwardList *dn = n->right;
  while (dn) {
    if (dn) dn = dn->right;
    if (dn) dn = dn->right;
    if (n) n = n->right;
    if (n == dn) return true;
  }
  return false;
}
