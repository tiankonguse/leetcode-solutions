// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<ll> preSum;
  ll GetSum(int l, int r) {  //[l, r]
    return preSum[r + 1] - preSum[l];
  }
  ll Solver(int fre, const vector<int>& nums) {  //
    const int n = nums.size();
    ll ans = GetSum(0, fre - 1);  // 前 fre 个都修改为 0
    for (int i = 0; i < n; i++) {
      const int l = i;
      const int r = l + fre - 1;
      if (r > n) break;  // [l, r]

      const int mid = (l + r) / 2;  // 可以证明，选择中间的最优
      const ll val = nums[mid];
      const int leftNum = mid - l + 1;
      const ll leftSum = GetSum(l, mid);  // [l, mid]
      const int rightNum = r - mid;
      const ll rightSum = GetSum(mid + 1, r);  // (mid, r]
      const ll tmpAns = leftNum * val - leftSum + rightSum - rightNum * val;
      ans = min(ans, tmpAns);
    }

    return ans;
  };

 public:
  int maxFrequencyScore(vector<int>& nums, const ll k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    preSum.reserve(n + 1);
    preSum.push_back(0);
    for (ll v : nums) {
      preSum.push_back(v + preSum.back());
    }

    int l = 1, r = n + 1;  //[l, r)
    while (l < r) {
      int mid = (l + r) / 2;
      if (Solver(mid, nums) <= k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }
};