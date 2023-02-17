#ifndef _LIST_HPP_
#define _LIST_HPP_

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


// TODO: double linked list

#endif  // _LIST_HPP_
