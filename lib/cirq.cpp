#include "include/cirq.hpp"

#include <cstdlib>

bool CircularQueue::Empty() {
  return (this->front_index == this->back_index);
}

int CircularQueue::Size() {
  return (this->front_index <= this->back_index)
      ? this->back_index - this->front_index
      : this->capacity + this->back_index - this->front_index;
}

void CircularQueue::Push(int value) {
  this->array[this->back_index] = value;
  this->back_index = (this->back_index + 1) % this->capacity;
  if (this->front_index == this->back_index) {
    resize();
  }
}

void CircularQueue::Push(std::initializer_list<int> values) {
  for (auto it = values.begin(); it != values.end(); ++it) {
    Push(*it);
  }
}

int CircularQueue::Top() {
  return this->array[this->front_index];
}
  
void CircularQueue::Pop() {
  this->front_index = (this->front_index + 1) % this->capacity;
}

void CircularQueue::resize() {
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
