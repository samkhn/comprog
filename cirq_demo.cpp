// Circular Queue Demo
// TODO: implement circular linked list?

#include <initializer_list>
#include <stdio.h>
#include <stdlib.h>

class CircularQueue {
 public:
  int capacity;
  unsigned front_index;
  unsigned back_index;
  // TODO: replace int* with smart pointer?
  int *array;

  bool Empty() {
    return (this->front_index == this->back_index);
  }
  
  int  Size() {
    return (this->front_index <= this->back_index)
        ? this->back_index - this->front_index
        : this->capacity + this->back_index - this->front_index;
  }
  
  void Push(int value) {
    this->array[this->back_index] = value;
    this->back_index = (this->back_index + 1) % this->capacity;
    if (this->front_index == this->back_index) {
      resize();
    }
  }
  
  void Push(std::initializer_list<int> values) {
    for (auto it = values.begin(); it != values.end(); ++it) {
      Push(*it);
    }
  }
  
  int Top() {
    return this->array[this->front_index];
  }
  
  void Pop() {
    this->front_index = (this->front_index + 1) % this->capacity;
  }

 private:
  void resize() {
    int *old_array = this->array;
    int *new_array = (int *)calloc(2 * this->capacity, sizeof(int));
    for (int i = 0; i < this->capacity; ++i) {
      new_array[i] = old_array[i];
    }
    this->array = new_array;
    delete (old_array);
    this->back_index = this->capacity;
    this->capacity *= 2;
  }
};

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
