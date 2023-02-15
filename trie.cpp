/* Trie aka retrieval tree aka prefix tree
 * Can be used to implement dictionaries
 */

#include <cstdio>
#include <deque>
#include <string>
#include <unordered_map>


struct trie_node {
	char value;
	std::unordered_map<char, trie_node*> children;
};

struct trie {
	trie_node* root;
};

trie* new_trie(std::initializer_list<std::string_view> words);
int   add(trie *t, std::string_view word);
int   exists(trie *t, std::string_view word);
int   remove(trie *t, std::string_view word);


trie* new_trie(std::initializer_list<std::string_view> words)
{
	trie *t = new trie;
	t->root = new trie_node{ '^', {} };
	for (auto it = words.begin(); it != words.end(); ++it)
		add(t, *it);
	return t;
}

// Returns 1 on success, 0 on invalid argument or failure
int add(trie *t, std::string_view word)
{
	if (!t || word.empty())
		return 0;
	trie_node *traverse = t->root;
	for (auto c = word.begin(); c != word.end(); ++c) {
		if (!traverse)
			traverse = new trie_node { *c, {} };
		auto findc = traverse->children.find(*c);
		if (findc == traverse->children.end())
			traverse->children[*c] = new trie_node{ *c, {} };
		traverse = traverse->children[*c];
	}
	return 1;
}

// Returns 1 if found, 0 if not, -1 on invalid arguments
int exists(trie *t, std::string_view word)
{
	if (!t || word.empty())
		return -1;
	trie_node *traverse = t->root;
	for (auto c = word.begin(); c != word.end(); ++c) {
		if (!traverse)
			return 0;
		auto findc = traverse->children.find(*c);
		if (findc == traverse->children.end())
			return 0;
		traverse = (*findc).second;
	}
	return 1;
}

// Returns 1 on success, 0 on invalid argument or doesn't exist
int remove(trie *t, std::string_view word)
{
	if (!t || word.empty())
		return 0;
	trie_node *traverse = t->root;
	for (auto c = word.begin(); c != word.end(); ++c) {
		if (!traverse)
			return 0;
		auto findc = traverse->children.find(*c);
		if (findc == traverse->children.end())
			return 1;
		traverse = traverse->children.extract(*c).mapped();
	}
	return 1;
}

std::string serialize(trie *t)
{
	std::string s = "Serialized trie: ";
	trie_node *traverse = t->root;
	std::deque<trie_node *> queue;
	for (auto kv : traverse->children)
		queue.push_back(kv.second);
	while (!queue.empty()) {
		traverse = queue.front();
		queue.pop_front();
		s += traverse->value;
		s += ' ';
		for (auto kv : traverse->children)
			queue.push_back(kv.second);
	}
	return s;
}

int main()
{
	trie *dict = new_trie({"hello", "world"});
	if (exists(dict, "not in dict")) {
		printf("exists() returned word, want nothing\n");
		return -1;
	}
	if (!exists(dict, "hello")) {
		printf("exists(hello) returned not found, want found\n");
		return -1;
	}
	if (!add(dict, "sam")) {
		printf("add(sam) failed\n");
		return -1;
	}
	if (!exists(dict, "sam")) {
		printf("exists(sam) returned not found, want found\n");
		return -1;
	}
	printf("Dict,  pre-removal(world):\n %s\n", serialize(dict).c_str());
	if (!remove(dict, "world")) {
		printf("remove(world) failed\n");
		return -1;
	}
	printf("Dict, post-removal(world):\n %s\n", serialize(dict).c_str());
	return 0;
}
