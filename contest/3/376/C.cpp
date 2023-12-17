// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll minimumCost(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    ll n = nums.size();
    ll mid = 0;  // [0, mid)
    ll leftNum = 0;
    ll rightNum = n;
    ll leftSum = 0;
    ll rightSum = accumulate(nums.begin(), nums.end(), 0ll);
    ll maxVal = nums.back();
    ll ans = rightSum;

    for (ll base = 1;; base *= 10) {  // 一半最大 5 位
      const ll nextBase = base * 10;
      for (int offset = 10; offset >= 1; offset -= 9) {
        for (ll left = base; left < nextBase; left++) {
          ll tmp = left / offset;
          ll val = left;
          while (tmp) {
            val = val * 10 + (tmp % 10);
            tmp = tmp / 10;
          }

          // 更新游标，计算答案
          while (mid < n && nums[mid] <= val) {
            leftNum += 1;
            leftSum += nums[mid];
            rightNum -= 1;
            rightSum -= nums[mid];
            mid++;
          }
          ans = min(ans, val * leftNum - leftSum + rightSum - val * rightNum);

          if (val >= maxVal) {
            return ans;
          }
        }
      }
    }

    return ans;
  }
};
