// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int val = 0;
  int num = 0;
  int next[2];
};
Node nodes[max6];
const int BIT = 22;
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = false;
    node.val = 0;
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
  void Insert(int num) {
    int root = 0;
    for (int i = BIT; i >= 0; i--) {
      int v = (num >> i) & 1;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      nodes[root].num++;
      root = nodes[root].next[v];
    }
    nodes[root].num++;
    nodes[root].val = num;
    nodes[root].endFlag = 1;
  }
  void Remove(int num) {
    int root = 0;
    for (int i = BIT; i >= 0; i--) {
      int v = (num >> i) & 1;
      nodes[root].num--;
      root = nodes[root].next[v];
    }
    nodes[root].num--;
    nodes[root].val = 0;
    nodes[root].endFlag = 0;
  }

  /** Returns if the word is in the trie. */
  int Search(const int num, int root = 0, int index = BIT) {
    // 可以选择自己，所以肯定有答案
    while (index >= 0) {
      int v = (num >> index) & 1;
      int p1 = nodes[root].next[1 - v];
      if (p1 != -1 && nodes[p1].num > 0) {
        root = p1;
        index--;
        continue;
      }

      int p0 = nodes[root].next[v];
      if (p0 != -1 && nodes[p0].num > 0) {
        root = p0;
        index--;
        continue;
      }
      return 0;
    }
    return nodes[root].val ^ num;
  }
};

Trie trie;
class Solution {
 public:
  int maximumStrongPairXor(vector<int>& nums1) {
    int n = nums1.size();
    sort(nums1.begin(), nums1.end());
    vector<int> nums(n);
    nums.clear();
    unordered_set<int> h;
    for (auto v : nums1) {
      if (h.count(v) == 0) {
        nums.push_back(v);
        h.insert(v);
      }
    }

    trie.Init();
    n = nums.size();
    int ans = 0;
    // printf("begin\n");
    for (int i = 0, r = 0; i < n; i++) {  //[i, r)
      int y = nums[i];
      int y2 = y * 2;

      while (r < n && nums[r] <= y2) {
        // printf("insert i=%d r=%d y=%d y2=%d\n", i, r, nums[r], y2);
        trie.Insert(nums[r]);
        r++;
      }

      int tmp = trie.Search(y);
      // printf("[y=%d y2=%d], ans=%d\n", y, y2, tmp);
      ans = max(ans, tmp);

      // printf("remove i=%d y=%d\n", i, y);
      trie.Remove(y);
    }
    return ans;
  }
};