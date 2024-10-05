// #include <bits/stdc++.h>
/*
题目: 15. 三数之和
地址: https://leetcode.cn/problems/3sum/description/?envType=study-plan-v2&envId=top-100-liked
考察: 双指针
问题:  求所有的三元组，使得三元素之和为0.
思路1: 与两数之和类似，枚举一个数，然后使用双指针求答案。
时间复杂度: `O(n^2)`
空间复杂度: `O(1)`
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
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ans;
    int n = nums.size();    
    sort(nums.begin(), nums.end());
    int preVal = nums.front() - 1;
    for (int i = 0; i < n; i++) {
      const int nowVal = nums[i];
      if (nowVal == preVal) continue;

      int l = i + 1, r = n - 1;
      const int target = -nowVal;
      while (l < r) {
        const int sum = nums[l] + nums[r];
        if (sum > target) {
          r--;
        } else if (sum < target) {
          l++;
        } else {
          ans.push_back({nowVal, nums[l], nums[r]});
          l++;
          r--;
          while (l < r && nums[l - 1] == nums[l]) {
            l++;
          }
          while (l < r && nums[r] == nums[r + 1]) {
            r--;
          }
        }
      }
      preVal = nowVal;
    }

    return ans;
  }
};