// #include <bits/stdc++.h>
/*
题目： 283. 移动零
地址：
https://leetcode.cn/problems/move-zeroes/description/?envType=study-plan-v2&envId=top-100-liked
考察： 双指针
问题： 0移动到数组最后，要求原地移动，其他数字顺序不变
思路：
从前到后扫描，遇到0暂停慢指针，快指针遇到非0，与慢指针交换（快慢指针之间都是0）。
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
  vector<int> moveZeroes(vector<int>& nums) {
    int n = nums.size();
    int l = 0;
    for (int r = 0; r < n; r++) {
      if (nums[r] != 0) {
        swap(nums[l], nums[r]);
        l++;
      }
    }
    return nums;
  }
};