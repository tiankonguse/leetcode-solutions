// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int val = 0;
  int num = 0;
  int next[26];
};
Node nodes[max6];
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
  void Insert(const string& word, int val) {
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
    nodes[root].val = val;
  }

  /** Returns if the word is in the trie. */
  bool Search(const string& word, int root, int index, vector<int>& dp) {
    int n = word.length();
    int base = dp[index];
    while (index < n) {
      char c = word[index];
      int v = c - 'a';
      int p = nodes[root].next[v];
      if (p == -1) return false;
      root = p;
      index++;

      if (nodes[root].endFlag == 1) {
        int cost = base + nodes[root].val;
        if (dp[index] == -1) {
          dp[index] = cost;
        } else {
          dp[index] = min(dp[index], cost);
        }
      }
    }

    return nodes[root].endFlag == 1;
  }
};
Trie trie;

class Solution {
 public:
  int minimumCost(const string& target, vector<string>& words,
                  vector<int>& costs) {
    trie.Init();
    unordered_map<string, int> h;
    for (int i = 0; i < words.size(); i++) {
      string& w = words[i];
      int c = costs[i];
      if (h.count(w)) {
        h[w] = min(h[w], c);
      } else {
        h[w] = c;
      }
    }
    for (auto& [k, v] : h) {
      trie.Insert(k, v);
    }

    int n = target.size();
    vector<int> dp;
    dp.resize(n + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      if (dp[i] == -1) continue;
      trie.Search(target, 0, i, dp);
    }
    return dp[n];
  }
};