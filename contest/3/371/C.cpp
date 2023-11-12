// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<ll> dp;
  int n;
  ll Solver(vector<int>& nums1, vector<int>& nums2, int num1max, int num2Max) {
    dp.clear();
    dp.resize(n, INT_MAX);

    for (int i = 0; i < n; i++) {
      // 不交换
      if (nums1[i] <= num1max && nums2[i] <= num2Max) {
        if (i == 0) {
          dp[i] = min(dp[i], 0ll);
        } else {
          dp[i] = min(dp[i], dp[i - 1]);
        }
      }

      // 交换
      if (nums2[i] <= num1max && nums1[i] <= num2Max) {
        if (i == 0) {
          dp[i] = min(dp[i], 1ll);
        } else {
          dp[i] = min(dp[i], 1 + dp[i - 1]);
        }
      }
      // printf("i=%d ans=%lld\n", i, dp[i]);
    }
    return dp[n - 1];
  }

 public:
  int minOperations(vector<int>& nums1, vector<int>& nums2) {
    n = nums1.size();
    if (n == 1) return 0;

    ll ans1 = Solver(nums1, nums2, nums1.back(), nums2.back());
    ll ans2 = Solver(nums1, nums2, nums2.back(), nums1.back());
    ll ans = min(ans1, ans2);
    if (ans >= INT_MAX) {
      return -1;
    }
    return ans;
  }
};