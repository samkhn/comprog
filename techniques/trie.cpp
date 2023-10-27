// Tries

#include <stdio.h>

#include <deque>
#include <string>
#include <unordered_map>

struct Node {
  char value;
  std::unordered_map<char, Node *> children;
};

class Trie {
  Node *root;

 public:
  void New() { this->root = new Node{'^', {}}; }
  void New(std::initializer_list<std::string_view> words) {
    New();
    for (auto it = words.begin(); it != words.end(); ++it) {
      Add(*it);
    }
  }

  std::string Serialize() const {
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

  int Exists(std::string_view word) {
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

  int Add(std::string_view word) {
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

  int Remove(std::string_view word) {
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
};

int main() {
  Trie *dict = new Trie;
  dict->New({"hello", "world"});
  if (dict->Exists("not in dict")) {
    printf("exists() returned word, want nothing\n");
    return -1;
  }
  if (!dict->Exists("hello")) {
    printf("exists(hello) returned not found, want found\n");
    return -1;
  }
  if (!dict->Add("sam")) {
    printf("add(sam) failed\n");
    return -1;
  }
  if (!dict->Exists("sam")) {
    printf("exists(sam) returned not found, want found\n");
    return -1;
  }
  printf("Dict,  pre-removal(world):\n %s\n", dict->Serialize().c_str());
  if (!dict->Remove("world")) {
    printf("remove(world) failed\n");
    return -1;
  }
  printf("Dict, post-removal(world):\n %s\n", dict->Serialize().c_str());
  return 0;
}
