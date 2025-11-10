#include <bits/stdc++.h>
using namespace std;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int num = 0;
  int next[26];
};
Node nodes[max5];
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = false;
    node.num = 0;
    memset(node.next, -1, sizeof(node.next));
  }

  int Add() {
    int ret = index;
    Clear(ret);
    index++;
    return ret;
  }

 public:
  /** Initialize your data structure here. */
  Trie() { Init(); }

  void Init() {
    index = 0;
    Add();
  }

  /** Inserts a word into the trie. */
  void Insert(const string& word) {
    int root = 0;
    for (auto c : word) {
      int v = c - 'a';
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      nodes[root].num++;
      root = nodes[root].next[v];
    }
    nodes[root].num++;
    nodes[root].endFlag = 1;
  }

  /** Returns if the word is in the trie. */
  bool Search(const string& word, int root = 0, int index = 0) {
    int n = word.length();
    while (index < n) {
      char c = word[index];
      if (c == '.') {
        for (int v = 0; v < 26; v++) {
          int p = nodes[root].next[v];
          if (p == -1 && nodes[p].num > 0) continue;
          if (Search(word, p, index + 1)) {
            return true;
          }
        }

        return false;
      } else {
        int v = c - 'a';
        int p = nodes[root].next[v];
        if (p == -1 && nodes[p].num > 0) return false;
        root = p;
        index++;
      }
    }

    return nodes[root].endFlag == 1;
  }
};

Trie trie;
class WordDictionary {
 public:
  WordDictionary() { trie.Init(); }

  void addWord(const string& s) { trie.Insert(s); }

  bool search(const string& s) { return trie.Search(s); }
};

