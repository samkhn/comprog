// Trie aka retrieval tree aka prefix tree
// Can be used to implement dictionaries

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>


struct TrieNode {
	char value;
	std::unordered_map<char, TrieNode*> children;
};

struct Trie {
	TrieNode* root;
};
Trie* New(std::initializer_list<std::string_view> words);
int   Add(Trie *t, std::string_view word);
int   Exists(Trie *t, std::string_view word);
int   Remove(Trie *t, std::string_view word);


Trie* New(std::initializer_list<std::string_view> words) {
	Trie *t = new Trie;
	t->root = new TrieNode{ '^', {} };
	for (auto it = words.begin(); it != words.end(); ++it) {
		Add(t, *it);
	}
	return t;
}

// Returns 1 on success, 0 on invalid argument or failure
int Add(Trie *t, std::string_view word) {
	if (!t || word.empty())
		return 0;
	TrieNode *traverse = t->root;
	for (auto c = word.begin(); c != word.end(); ++c) {
		if (!traverse)
			traverse = new TrieNode { *c, {} };
		auto findc = traverse->children.find(*c);
		if (findc == traverse->children.end())
			traverse->children[*c] = new TrieNode{ *c, {} };
		traverse = traverse->children[*c];
	}
	return 1;
}

// Returns 1 if found, 0 if not, -1 on invalid arguments
int Exists(Trie *t, std::string_view word) {
	if (!t || word.empty())
		return -1;
	TrieNode *traverse = t->root;
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
int Remove(Trie *t, std::string_view word) {
	if (!t || word.empty())
		return 0;
	TrieNode *traverse = t->root;
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

std::string Serialize(Trie *t) {
	std::string s = "BFS: ";
	TrieNode *traverse = t->root;
	std::deque<TrieNode *> queue;
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

int main() {
	Trie *dict = New({"hello", "world"});
	if (Exists(dict, "not in dict")) {
		std::cout << "Not existenct word found in dict\n";
		return -1;
	}
	if (!Exists(dict, "hello")) {
		std::cout << "hello not found in dict when it should be there\n";
		return -1;
	}
	if (!Add(dict, "sam")) {
		std::cout << "Failed to add word sam to dict\n";
		return -1;
	}
	if (!Exists(dict, "sam")) {
		std::cout << "sam not found in dict when it should be there\n";
		return -1;
	}
	std::cout << "DICT pre-removal:\n" << Serialize(dict) << "\n";
	if (!Remove(dict, "world")) {
		std::cout << "Failed to remove 'world' from dict\n";
		return -1;
	}
	std::cout << "DICT post-removal of world:\n" << Serialize(dict) << "\n";  
	return 0;
}
