// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumEnergy(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> dp(n, 0);
    ll ans = nums.back();
    for (int i = n - 1; i >= 0; i--) {
      if (i + k >= n) {
        dp[i] = nums[i];
      } else {
        dp[i] = nums[i] + dp[i + k];
      }
      ans = max(ans, dp[i]);
    }
    return ans;
  }
};