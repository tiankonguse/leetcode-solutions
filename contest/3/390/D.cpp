// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int num = 0;
  int len = max6;    // 当前前缀最短的答案
  int index = max6;  // 当前的答案
  int next[26];
};
Node nodes[max6];
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = false;
    node.num = 0;
    node.len = max6;
    node.index = max6;
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
  void Insert(const string& word, const int index) {
    const int len = word.size();
    int root = 0;
    nodes[root].num++;
    if (len < nodes[root].len) {
      nodes[root].len = len;
      nodes[root].index = index;
    } else if (len == nodes[root].len && index < nodes[root].index) {
      nodes[root].index = index;
    }

    for (auto c : word) {
      int v = c - 'a';
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      root = nodes[root].next[v];
      nodes[root].num++;
      if (len < nodes[root].len) {
        nodes[root].len = len;
        nodes[root].index = index;
      } else if (len == nodes[root].len && index < nodes[root].index) {
        nodes[root].index = index;
      }
    }
    nodes[root].endFlag = 1;
  }

  /** Returns if the word is in the trie. */
  int Search(const string& word, int root = 0, int index = 0) {
    int n = word.length();
    while (index < n) {
      char c = word[index];
      int v = c - 'a';
      int p = nodes[root].next[v];
      if (p == -1) {  // root 是公共前缀
        return nodes[root].index;
      }
      root = p;
      index++;
    }

    return nodes[root].index;
  }
};

Trie trie;
class Solution {
 public:
  vector<int> stringIndices(vector<string>& words, vector<string>& query) {
    trie.Init();
    for (int i = 0; i < words.size(); i++) {
      auto& v = words[i];
      std::reverse(v.begin(), v.end());
      trie.Insert(v, i);
    }
    for (auto& v : query) {
      std::reverse(v.begin(), v.end());
    }

    vector<int> ans;
    ans.reserve(query.size());
    for (auto& q : query) {
      ans.push_back(trie.Search(q));
    }
    return ans;
  }
};