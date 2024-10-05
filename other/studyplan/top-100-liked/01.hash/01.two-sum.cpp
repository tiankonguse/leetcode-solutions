// #include <bits/stdc++.h>
/*
题目： 1. 两数之和
地址：https://leetcode.cn/problems/two-sum/?envType=study-plan-v2&envId=top-100-liked
考察：hash
问题：问是否存在两个数字之和等于目标数字，存在是返回两个数字的下标。  
思路：hash 查找差值是否存在
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
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<ll, ll> h;
    for (int i = 0; i < nums.size(); i++) {
      ll v = nums[i];
      if (h.count(target - v)) {
        return {int(h[target - v]), i};
      }
      h[v] = i;
    }
    return {-1, -1};
  }
};