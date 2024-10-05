// #include <bits/stdc++.h>
/*
题目： 128. 最长连续序列
地址：https://leetcode.cn/problems/longest-consecutive-sequence/description/?envType=study-plan-v2&envId=top-100-liked
考察：hash、并查集
问题：给一个数组，问挑选尽量多的数字，使得数字连续。要求复杂度不超过`O(n)`
思路：hash 储存，分组边合并边求答案
时间复杂度：`O(n)`
空间复杂度：`O(n)`
*/

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> h;
    for (auto v : nums) {
      h[v] = -1;
    }
    int ans = 0;
    for (auto v : nums) {
      if (h[v] != -1) continue;  // 已经计算过了

      int num = 1;
      int p = v + 1;
      while (h.count(p)) {
        if (h[p] != -1) {
          num += h[p];
          break;
        }

        h[p] = 1;
        p++;
        num++;
      }
      h[v] = num;
      ans = max(ans, num);
    }

    return ans;
  }
};