// #include <bits/stdc++.h>
/*
题目: 3. 无重复字符的最长子串
地址:
https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/?envType=study-plan-v2&envId=top-100-liked
考察: 滑动窗口
问题:  求最长的不含重复字符的子串
思路1: 滑动窗口, 枚举左边界，找到右边界, 边界左闭右开 [l, r)
时间复杂度: `O(n)`
空间复杂度: `O(n)`
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
  int lengthOfLongestSubstring(const string& s) {
    unordered_set<char> h;
    int ans = 0;
    int l = 0, r = 0;
    int n = s.length();
    for (int l = 0; l < n; l++) {
      while (r < n && h.count(s[r]) == 0) {
        h.insert(s[r]);
        r++;
      }

      ans = max(ans, r - l);
      h.erase(s[l]);
    }
    return ans;
  }
};