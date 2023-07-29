// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int len = 0;
  int next[26];
};
Node nodes[max6];
class Trie {
  int index = 0;

  int Add(int len = 0) {
    int ret = index;
    Node& node = nodes[ret];
    node.endFlag = false;
    node.len = len;
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
  void Insert(const string& word) {
    int root = 0;
    for (auto c : word) {
      int v = c - 'a';
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add(nodes[root].len + 1);
      }
      root = nodes[root].next[v];
    }
    nodes[root].endFlag = 1;
  }

  /** Returns if the word is in the trie. */
  pair<bool, int> Search(const string& word, int root = 0, int index = 0,
                         int n = -1) {
    if (n == -1) {
      n = word.length();
    }
    while (index < n) {
      char c = word[index];
      int v = c - 'a';
      int p = nodes[root].next[v];
      if (p == -1) return {false, -1};
      root = p;
      index++;

      if (nodes[root].endFlag == 1) {
        return {true, nodes[root].len};
      }
    }

    return {false, -1};
  }
};

Trie trie;

class Solution {
 public:
  int longestValidSubstring(const string& word, vector<string>& forbidden) {
    trie.Init();
    for (auto& s : forbidden) {
      trie.Insert(s);
    }

    int ans = 0;
    int pre = 0;
    for (int i = 0; i < word.size(); i++) {
      auto [flag, len] = trie.Search(word, 0, i);
      if (!flag) {
        ans = max(ans, i - pre + 1);
        // printf("ans=%d i=%d flag=%d pre=%d, len=%d\n", ans, i, flag, pre,
        // len);
      } else {
        int maxN = i + len;
        int offset = i;
        for (int j = maxN - 1; j >= i; j--) {
          auto [flag, len] = trie.Search(word, 0, j, maxN);
          if(flag){
            maxN = j + len - 1;
          }
        }
        ans = max(ans, maxN - pre);
        // printf("ans=%d i=%d flag=%d pre=%d, len=%d\n", ans, i, flag, pre,
        // len);
        pre = i + 1;
      }
    }

    return ans;
  }
};