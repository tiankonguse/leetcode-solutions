
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;

const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
struct Node {
  int endFlag = 0;  // 是否是结束标示符
  int num = 0;
  int next[2];
};
Node nodes[max5];
const int MaxBit = 15;
class Trie {
  int index = 0;

  void Clear(int root) {
    Node& node = nodes[root];
    node.endFlag = 0;
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
  void Insert(const int word) {
    int root = 0;
    for (int i = MaxBit - 1; i >= 0; i--) {
      int v = (word >> i) & 1;
      if (nodes[root].next[v] == -1) {
        nodes[root].next[v] = Add();
      }
      nodes[root].num++;
      root = nodes[root].next[v];
    }
    nodes[root].num++;
    nodes[root].endFlag = word;
  }
  void Erase(const int word) {
    int root = 0;
    for (int i = MaxBit - 1; i >= 0; i--) {
      int v = (word >> i) & 1;
      nodes[root].num--;
      root = nodes[root].next[v];
    }
    nodes[root].num--;
  }
  int Count(int root) {
    return nodes[root].num;  // 返回子树的节点数
  }

  /** Returns if the word is in the trie. */
  int Search(const int& word) {
    int root = 0;
    for (int i = MaxBit - 1; i >= 0; i--) {
      int v = (word >> i) & 1;
      v = 1 - v;  // 优先选择相反的 bit
      if (nodes[root].next[v] == -1 || Count(nodes[root].next[v]) == 0) {
        root = nodes[root].next[1 - v];
      } else {
        root = nodes[root].next[v];
      }
    }
    return nodes[root].endFlag ^ word;
  }
};

Trie trie;
class Solution {
 public:
  int maxXor(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> preSum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      preSum[i] = preSum[i - 1] ^ nums[i - 1];
    }

    int ans = 0;
    deque<pair<int, int>> maxVal, minVal;
    int leftOffset = 0;
    trie.Init();
    trie.Insert(preSum[leftOffset]);
    for (int i = 1; i <= n; i++) {
      const int v = nums[i - 1];
      while (!maxVal.empty() && maxVal.back().first <= v) {
        maxVal.pop_back();
      }
      maxVal.push_back({v, i});
      while (!minVal.empty() && minVal.back().first >= v) {
        minVal.pop_back();
      }
      minVal.push_back({v, i});
      while (maxVal.front().first - minVal.front().first > k) {
        int offset;
        if (maxVal.front().second < minVal.front().second) {
          offset = maxVal.front().second;
          maxVal.pop_front();
        } else {
          offset = minVal.front().second;
          minVal.pop_front();
        }
        // [leftOffset, offset) 的前缀和都需要删除
        while (leftOffset < offset) {
          trie.Erase(preSum[leftOffset]);
          leftOffset++;
        }
      }
      MyPrintf("v=%d maxVal={%d,%d} minVal={%d,%d} leftOffset=%d, i=%d\n", v, maxVal.front().first,
               maxVal.front().second, minVal.front().first, minVal.front().second, leftOffset, i);
      // 左端点为 (leftOffset, i] ，右端点为 i 的子数组都满足条件
      ans = max(ans, trie.Search(preSum[i]));
      trie.Insert(preSum[i]);
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif