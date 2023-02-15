/* Linked List
 * We explore two types: Forward List (single linked list) and List (double
 * linked list).
 */


#include <initializer_list>
#include <string>


struct forward_list {
	int value;
	forward_list *right;
};
static constexpr forward_list kSentinelFL = forward_list{
	0,
	nullptr
};


forward_list* back(forward_list *fl)
{
	if (!fl->right)
		return fl;
	forward_list *r = fl;
	while (fl) {
		r = fl;
		fl = fl->right;
	}
	return r;
}

forward_list* add(forward_list *to, forward_list *n)
{
	if (!to)
		return n;
	back(to)->right = n;
	return n;
}

forward_list* add(forward_list *to, int value)
{
	return add(to, new forward_list{
			value,
			nullptr
		});
}

forward_list* add(forward_list *to, std::initializer_list<int> values)
{
	for (auto it = values.begin(); it != values.end(); it++)
		to = add(to, *it);
	return to;
}

forward_list* new_forward_list(std::initializer_list<int> values)
{
	if (values.begin() == values.end())
		return nullptr;
	forward_list *n = new forward_list{
		0,
		nullptr
	};
	forward_list *i = n;
	auto it = values.begin();
	n->value = *it++;
	for (; it != values.end(); it++)
		i = add(i, *it);
	return n;
}

std::string serialize(forward_list *fl)
{
	std::string s = "";
	while (fl) {
		s.append(std::to_string(fl->value));
		s.append(" ");
		fl = fl->right;
	}
	return s;
}

int count(forward_list *fl)
{
	int c = 0;
	while (fl) {
		c++;
		fl = fl->right;
	}
	return c;
}

forward_list* merge(forward_list *l, forward_list *r)
{
	if (!l)
		return r;
	if (!r)
		return l;
	back(l)->right = r;
	return l;
}

forward_list* reverse(forward_list *n)
{
	forward_list *f = n;
	forward_list *b = back(n);
	forward_list *start = f;
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

bool has_cycle(forward_list *n)
{
	forward_list *dn = n->right;
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


// Node is the start of a double linked list
// struct node {
// 	int value;
// 	node *left;
// 	node *right;
// };
// static constexpr node kSentinelL = node{0, nullptr, nullptr};
// node* add(Node *to, Node *n) {}
// node* add(Node *to, int value) {}
// node* add(Node *to, std::initializer_list<int> values) {}
// node* new(std::initializer_list<int> values) {}
// std::string serialize(node *l) {}
// int count(node *l) {}
// node* merge(node *l, node *r) {}
// node* reverse(node *n) {}
// bool has_cycle(node *n) {}


int main()
{
	forward_list *fl = new_forward_list({});
	printf("empty fl contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = new_forward_list({0});
	printf("fl({0}) contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = new_forward_list({10, 2, 4, 14, -2});
	printf("fl({10,2,4,14,-2}) contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());
	add(fl, 11);
	add(fl, {-1, -4});
	add(fl, {});
	printf("fl, after a few adds, contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = add(nullptr, 0);
	printf("add(null, 0) generated list w/ %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	forward_list *o = new_forward_list({14, 15});
	forward_list *l = new_forward_list({1, -23});
	fl = merge(o, l);
	printf("fl merge created list w/ %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());
	fl = merge(fl, new_forward_list({}));
	printf("fl merge w/ empty created list w/ %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());
	fl = merge(new_forward_list({}), fl);
	printf("empty merge w/ fl created list w/ %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = new_forward_list({1, 2, 3, 4, 5, 6, 7});
	printf("fl unreversed contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());
	fl = reverse(fl);
	printf("fl reversed contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = reverse(new_forward_list({11}));
	printf("fl({11}) reversed contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	fl = reverse(new_forward_list({0, 1}));
	printf("{0,1} reversed contains %d nodes : { %s }\n",
		count(fl), serialize(fl).c_str());

	forward_list *nocycle = new_forward_list({1});
	printf("Cycle in {1->null} ?: %d\n", has_cycle(nocycle));
	nocycle = new_forward_list({1, 2, 3, 4});
	printf("Cycle in {1->2->3->4->null} ?: %d\n", has_cycle(nocycle));
	forward_list *cycle = nocycle;
	forward_list *b = back(cycle);
	add(b, cycle);  // Create cycle
	printf("Cycle in {1->2->3->4->1} ?: %d\n", has_cycle(cycle));

	return 0;
}
