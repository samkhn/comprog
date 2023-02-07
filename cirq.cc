// Circular Queue
// A queue implemented with a circular buffer
// TODO: implement with linked list

#include <cstdlib>
#include <format>
#include <iostream>

struct CirQ {
  int capacity;
  unsigned front_index;
  unsigned back_index;
  int *array;
};

bool IsEmpty(CirQ *q) {
  return (q->front_index == q->back_index);
}

int Size(CirQ *q) {
  return (q->front_index <= q->back_index)
    ? q->back_index - q->front_index
    : q->capacity + q->back_index - q->front_index;
}

void resize(CirQ *q) {
  int *old_array = q->array;
  int *new_array = (int*)calloc(2*q->capacity, sizeof(int));
  for (int i = 0; i < q->capacity; ++i)
    new_array[i] = old_array[i];
  q->array = new_array;
  delete(old_array);
  std::cout << "Resizing"
	    << " from " << q->capacity
	    << " to " << q->capacity*2
	    << "\n";
  q->back_index = q->capacity;
  q->capacity *= 2;
}

void Push(CirQ *q, int value) {
  q->array[q->back_index] = value;	
  q->back_index = (q->back_index + 1) % q->capacity;
  if (q->front_index == q->back_index)
    resize(q);
  std::cout << "Inserted " << value << "\n";
}

void Push(CirQ *q, std::initializer_list<int> values) {
  for (auto it = values.begin(); it != values.end(); ++it)
    Push(q, *it);
}

int Pop(CirQ *q) {
  int v = q->array[q->front_index];
  q->front_index = (q->front_index + 1) % q->capacity;
  return v;
}

int* Top(CirQ *q) {
  return &q->array[q->front_index];
}

int main() {
  CirQ *q = new CirQ{
    .capacity{3},
    .front_index{0},
    .back_index{0},
    .array{(int*)calloc(3, sizeof(int))}
  };
  std::cout << std::format("Q empty?: {0}\n", IsEmpty(q));
  Push(q, 10);
  std::cout << std::format("Q size: {0}\n", Size(q))
	    << std::format("Q empty?: {0}\n", IsEmpty(q))
	    << std::format("Q top?: {0}\n", *Top(q));
  Push(q, 15);
  Push(q, {-1, 3, 11, 100, 2, 123, -14});
  Pop(q);
  std::cout << std::format("Q size: {0}\n", Size(q))
	    << std::format("Q empty?: {0}\n", IsEmpty(q))
	    << std::format("Q top?: {0}\n", *Top(q));
  return 0;
}
