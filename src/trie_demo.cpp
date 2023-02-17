#include "include/trie.hpp"

#include <cstdio>

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
