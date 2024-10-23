#include <bits/stdc++.h>

#include "base.h"
using namespace std;

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

  // 不能直接删除，只需要使用 num 打标记即可
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

  /** 返回区间内异或最大的值 */
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

      // 不存在
      return -1;
    }
    return nodes[root].val;
  }
};

Trie trie;