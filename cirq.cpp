// Circular Queue
// A queue implemented with a circular buffer
// TODO: implement with linked list

#include <cstdlib>
#include <cstdio>
#include <initializer_list>

struct cirq {
	int capacity;
	unsigned front_index;
	unsigned back_index;
	int *array;
};

bool is_empty(cirq *q)
{
	return (q->front_index == q->back_index);
}

int size(cirq *q)
{
	return (q->front_index <= q->back_index)
		? q->back_index - q->front_index
		: q->capacity + q->back_index - q->front_index;
}

void _resize(cirq *q)
{
	int *old_array = q->array;
	int *new_array = (int*)calloc(2*q->capacity, sizeof(int));
	for (int i = 0; i < q->capacity; ++i)
		new_array[i] = old_array[i];
	q->array = new_array;
	delete(old_array);
	q->back_index = q->capacity;
	q->capacity *= 2;
}

void push(cirq *q, int value)
{
	q->array[q->back_index] = value;
	q->back_index = (q->back_index + 1) % q->capacity;
	if (q->front_index == q->back_index)
		_resize(q);
}

void push(cirq *q, std::initializer_list<int> values)
{
	for (auto it = values.begin(); it != values.end(); ++it)
		push(q, *it);
}

int pop(cirq *q)
{
	int v = q->array[q->front_index];
	q->front_index = (q->front_index + 1) % q->capacity;
	return v;
}

int* top(cirq *q)
{
	return &q->array[q->front_index];
}

int main()
{
	cirq *q = new cirq{
		3,
		0,
		0,
		(int*)calloc(3, sizeof(int))
	};
	printf("Q empty? %d\n", is_empty(q));
	push(q, 10);
	int *t = top(q);
	if (!t) {
		printf("Error: top(q) got nullptr, expected value\n");
		return -1;
	}
	printf("Q size: %d\nQ empty? %d\nQ top? %d\n",
		size(q), is_empty(q), *t);
	push(q, 15);
	push(q, {-1, 3, 11, 100, 2, 123, -14});
	pop(q);
	t = top(q);
	if (!t) {
		printf("Error: top(q) got nullptr, expected value\n");
		return -1;
	}
	printf("Q size: %d\nQ empty? %d\nQ top? %d\n",
		size(q), is_empty(q), *t);
	return 0;
}
