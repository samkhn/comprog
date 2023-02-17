#ifndef _CIRQ_HPP_
#define _CIRQ_HPP_

#include <initializer_list>

#include <stdlib.h>  // to access malloc/calloc

// A queue implemented with a circular buffer
class CircularQueue {
 public:
  int capacity;
  unsigned front_index;
  unsigned back_index;
  // TODO: replace int* with smart pointer?
  int *array;

  bool Empty();
  int  Size();
  void Push(int value);
  void Push(std::initializer_list<int> values);
  int  Top();  
  void Pop();

 private:
  void resize();
};

// TODO(samkhn): implement with linked list

#endif  // _CIRQ_HPP_
