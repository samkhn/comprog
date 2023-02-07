// Linked list

#include <format>
#include <iostream>

struct Node {
    int value;
    Node *prev;
    Node *next;
};

Node* AddNext(Node *to, Node *n)
{
    to->next = n;
    return n;
}

Node* AddNext(Node *to, int value)
{
    Node *n = new Node {
	.value{value},
	.prev{nullptr},
	.next{nullptr}
    };
    return AddNext(to, n);
}

Node* AddPrev(Node *to, Node *n)
{
    to->prev = n;
    return n;
}

Node* AddPrev(Node *to, int value)
{
    Node *n = new Node {
	.value{value},
	.prev{nullptr},
	.next{nullptr}
    };
    return AddPrev(to, n);
}

void PrintF(Node *n)
{
    while (n) {
	std::cout << n->value << " ";
	n = n->next;
    }
}

void PrintB(Node *n)
{
    while (n) {
	std::cout << n->value << " ";
	n = n->prev;
    }
}

std::string StringF(Node *n)
{
    std::string s;
    while (n) {
	s += std::format("{0} ", n->value);
	n = n->next;
    }
    return s;
}

std::string StringB(Node *n)
{
    std::string s;
    while (n) {
	s += std::format("{0} ", n->value);
	n = n->prev;
    }
    return s;
}

int CountF(Node *n)
{
    unsigned c = 0;
    while (n) {
	c++;
	n = n->next;
    }
    return c;
}

int CountB(Node *n)
{
    unsigned c = 0;
    while (n) {
	c++;
	n = n->prev;
    }
    return c;
}

Node* Back(Node *n)
{
    Node *b = nullptr;
    while (n) {
	b = n;
	n = n->next;
    }
    return b;
}

Node* Front(Node *n)
{
    Node *b = nullptr;
    while (n) {
	b = n;
	n = n->prev;
    }
    return b;
}

// head must point to double linked list
Node* Middle(Node *n)
{
    return nullptr;
}

// Undefined behavior if l and r point to different kinds of lists.
Node* Merge(Node *l, Node r)
{
    return nullptr;
}

int Reverse(Node *n)
{
    return -1;
}

// TODO: use two pointers to get the kth from last node
// TODO: use two pointers to detect cycles in the ll
// TODO: truncate a linked list
// TODO: swap value of nodes
// TODO: sentinel nodes to stop computation
int main()
{
    Node *fl = new Node;
    fl->value = -1;
	
    Node *n = AddNext(fl, 4);
    n = AddNext(n, 3);
    n = AddNext(n, 5);
    n = AddNext(n, 2);
	
    std::cout << std::format("fl: {0}\n", StringF(fl))
	      << std::format("fl has {0} elements\n", CountF(fl))
	      << std::format("back(fl) contains value {0}\n",
			     Back(fl)->value);
    return 0;
}
