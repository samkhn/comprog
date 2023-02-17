#include "include/list.hpp"

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
  Add(b, cycle);  // Create cycle
  printf("Cycle in {1->2->3->4->1} ?: %d\n", HasCycle(cycle));

  return 0;
}
