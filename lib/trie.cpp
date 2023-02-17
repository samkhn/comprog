#include "include/trie.hpp"

#include <deque>

void Trie::New() {
  this->root = new Node{'^', {}};
}

void Trie::New(std::initializer_list<std::string_view> words) {
  New();
  for (auto it = words.begin(); it != words.end(); ++it) {
    Add(*it);
  }
}

int Trie::Add(std::string_view word) {
  Node *traverse = root;
  for (auto c = word.begin(); c != word.end(); ++c) {
    if (!traverse) {
      traverse = new Node{*c, {}};
    }
    auto findc = traverse->children.find(*c);
    if (findc == traverse->children.end()) {
      traverse->children[*c] = new Node{*c, {}};
    }
    traverse = traverse->children[*c];
  }
  return 1;
}

int Trie::Exists(std::string_view word) {
  Node *traverse = root;
  for (auto c = word.begin(); c != word.end(); ++c) {
    if (!traverse) {
      return 0;
    }
    auto findc = traverse->children.find(*c);
    if (findc == traverse->children.end()) {
      return 0;
    }
    traverse = (*findc).second;
  }
  return 1;
}

int Trie::Remove(std::string_view word) {
  Node *traverse = root;
  for (auto c = word.begin(); c != word.end(); ++c) {
    if (!traverse) {
      return 0;
    }
    auto findc = traverse->children.find(*c);
    if (findc == traverse->children.end()) {
      return 1;
    }
    traverse = traverse->children.extract(*c).mapped();
  }
  return 1;
}

std::string Trie::Serialize() const {
  std::string s = "Serialized trie: ";
  Node *traverse = root;
  std::deque<Node *> queue;
  for (auto kv : traverse->children) {
    queue.push_back(kv.second);
  }
  while (!queue.empty()) {
    traverse = queue.front();
    queue.pop_front();
    s += traverse->value;
    s += ' ';
    for (auto kv : traverse->children) {
      queue.push_back(kv.second);
    }
  }
  return s;
}

