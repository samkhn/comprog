// List
// TODO: double linked list

#include <initializer_list>
#include <string>

struct ForwardList {
  int value;
  ForwardList *right;
};
static constexpr ForwardList kSentinelFLNode = ForwardList{0, nullptr};

std::string Serialize(ForwardList *fl);
ForwardList *Back(ForwardList *fl);
ForwardList *Add(ForwardList *to, ForwardList *n);
ForwardList *Add(ForwardList *to, int value);
ForwardList *Add(ForwardList *to, std::initializer_list<int> values);
ForwardList *NewForwardList(std::initializer_list<int> values);
ForwardList *Merge(ForwardList *l, ForwardList *r);
int Count(ForwardList *fl);
ForwardList *Reverse(ForwardList *n);
bool HasCycle(ForwardList *n);

ForwardList *Back(ForwardList *fl) {
  if (!fl->right)
    return fl;
  ForwardList *r = fl;
  while (fl) {
    r = fl;
    fl = fl->right;
  }
  return r;
}

ForwardList *Add(ForwardList *to, ForwardList *n) {
  if (!to)
    return n;
  Back(to)->right = n;
  return n;
}

ForwardList *Add(ForwardList *to, int value) {
  return Add(to, new ForwardList{value, nullptr});
}

ForwardList *Add(ForwardList *to, std::initializer_list<int> values) {
  for (auto it = values.begin(); it != values.end(); it++)
    to = Add(to, *it);
  return to;
}

ForwardList *NewForwardList(std::initializer_list<int> values) {
  if (values.begin() == values.end())
    return nullptr;
  ForwardList *n = new ForwardList{0, nullptr};
  ForwardList *i = n;
  auto it = values.begin();
  n->value = *it++;
  for (; it != values.end(); it++)
    i = Add(i, *it);
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
  if (!l)
    return r;
  if (!r)
    return l;
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
    if (dn)
      dn = dn->right;
    if (dn)
      dn = dn->right;
    if (n)
      n = n->right;
    if (n == dn)
      return true;
  }
  return false;
}

int main() {
  ForwardList *fl = NewForwardList({});
  printf("empty fl contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = NewForwardList({0});
  printf("fl({0}) contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = NewForwardList({10, 2, 4, 14, -2});
  printf("fl({10,2,4,14,-2}) contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());
  Add(fl, 11);
  Add(fl, {-1, -4});
  Add(fl, {});
  printf("fl, after a few adds, contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = Add(nullptr, 0);
  printf("Add(null, 0) generated list w/ %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  ForwardList *o = NewForwardList({14, 15});
  ForwardList *l = NewForwardList({1, -23});
  fl = Merge(o, l);
  printf("fl merge created list w/ %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());
  fl = Merge(fl, NewForwardList({}));
  printf("fl merge w/ empty created list w/ %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());
  fl = Merge(NewForwardList({}), fl);
  printf("empty merge w/ fl created list w/ %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = NewForwardList({1, 2, 3, 4, 5, 6, 7});
  printf("fl unreversed contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());
  fl = Reverse(fl);
  printf("fl reversed contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = Reverse(NewForwardList({11}));
  printf("fl({11}) reversed contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  fl = Reverse(NewForwardList({0, 1}));
  printf("{0,1} reversed contains %d nodes : { %s }\n", Count(fl),
         Serialize(fl).c_str());

  ForwardList *nocycle = NewForwardList({1});
  printf("Cycle in {1->null} ?: %d\n", HasCycle(nocycle));
  nocycle = NewForwardList({1, 2, 3, 4});
  printf("Cycle in {1->2->3->4->null} ?: %d\n", HasCycle(nocycle));
  ForwardList *cycle = nocycle;
  ForwardList *b = Back(cycle);
  Add(b, cycle); // Create cycle
  printf("Cycle in {1->2->3->4->1} ?: %d\n", HasCycle(cycle));

  return 0;
}
