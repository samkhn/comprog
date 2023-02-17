#ifndef _TRIE_HPP_
#define _TRIE_HPP_

#include <unordered_map>
#include <string>

struct Node {
  char value;
  std::unordered_map<char, Node *> children;
};

class Trie {
  Node *root;
 public:
  void New();
  void New(std::initializer_list<std::string_view> words);

  std::string Serialize() const;

  int Add(std::string_view word);
  int Exists(std::string_view word);
  int Remove(std::string_view word);
};

#endif  // _TRIE_HPP_
