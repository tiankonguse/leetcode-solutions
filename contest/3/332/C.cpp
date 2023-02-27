// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 4000010;
const int N = 10;
const char Base = '0';
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int next[N];
  int val = -1;
};
Node nodes[max6];
unordered_map<int, int> h;
int searchIndex = -1;

class Trie {
  int index = 0;

  int Add() {
    int ret = index;
    Node& node = nodes[ret];
    node.endFlag = false;
    memset(node.next, -1, sizeof(node.next));
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
  void Insert(const string& word, int val) {
    int root = 0;
    for (auto c : word) {
      int v = c - Base;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      root = nodes[root].next[v];
    }
    nodes[root].endFlag = 1;
    nodes[root].val = val;
    h[val] = -1;
  }

  /** Returns if the word is in the trie. */
  void Search(const string& word, int root = 0, int index = 0) {
    int n = word.length();
    while (index < n) {
      char c = word[index];
      int v = c - Base;
      int p = nodes[root].next[v];
      if (p == -1) return;
      root = p;
      if (nodes[root].endFlag && h[nodes[root].val] == -1) {
        h[nodes[root].val] = searchIndex;
      }
      index++;
    }
  }
};

Trie trie;
class Solution {
  void ToV2(int v, string& s) {
    s.reserve(32);
    s.clear();
    if (v == 0) {
      s.push_back('0');
      return;
    }

    while (v) {
      s.push_back('0' + (v % 2));
      v /= 2;
    }
    std::reverse(s.begin(), s.end());
  }

 public:
  vector<vector<int>> substringXorQueries(const string& s,
                                          vector<vector<int>>& queries) {
    trie.Init();
    string v;
    for (auto& q : queries) {
      int val = q[0] ^ q[1];
      ToV2(val, v);
      trie.Insert(v, val);
    }

    for (int i = 0; i < s.size(); i++) {
      searchIndex = i;
      trie.Search(s, 0, i);
    }

    vector<vector<int>> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int val = q[0] ^ q[1];
      ToV2(val, v);
      int p = h[val];
      if (p == -1) {
        ans.push_back({-1, -1});
      } else {
        ans.push_back({p, p + int(v.size()) - 1});
      }
    }

    return ans;
  }
};