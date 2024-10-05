// #include <bits/stdc++.h>
/*
题目： 11. 盛最多水的容器
地址：
https://leetcode.cn/problems/container-with-most-water/description/?envType=study-plan-v2&envId=top-100-liked
考察： 双指针
问题： 给一排建筑的高度，问那两个建筑之间可以存最多的水。
思路： 枚举水的高度，移动左右边界，使得边界高度不低于水位
时间复杂度： `O(n)`
空间复杂度： `O(1)`
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
  int maxArea(vector<int>& height) {
    int n = height.size();
    int l = 0, r = n - 1;
    int h = 0;
    int ans = 0;
    while (l < r) {
      if (height[l] < h) {
        l++;
        continue;
      }
      if (height[r] < h) {
        r--;
        continue;
      }
      h = min(height[r], height[l]); // 可能都大于水位，快速对齐水位
      ans = max(ans, h * (r - l));
      h++;
    }

    return ans;
  }
};