// Circular Queue Demo

#include "include/cirq.hpp"

#include <stdio.h>

int main() {
  CircularQueue *q = new CircularQueue{
    3,
    0,
    0,
    (int *)calloc(3, sizeof(int))
  };
  printf("Q empty? %d\n", q->Empty());
  q->Push(10);
  printf("Q size: %d\nQ top? %d\n", q->Size(), q->Top());
  q->Push(15);
  q->Push(10);
  q->Push({-1, 3, 11, 100, 2, 123, -14});
  q->Pop();
  printf("Q size: %d\nQ top? %d\n", q->Size(), q->Top());
  return 0;
}
