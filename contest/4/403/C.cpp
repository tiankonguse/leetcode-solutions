// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long maximumTotalCost(vector<int>& nums) {
    int n = nums.size();
    vector<vector<ll>> dp(n + 3, vector<ll>(2, 0));

    for (int i = n - 1; i >= 0; i--) {
      // 0 正负号
      dp[i][0] = max(nums[i] + dp[i + 1][0], nums[i] + dp[i + 1][1]);
      dp[i][1] = -nums[i] + dp[i + 1][0];
    }
    return dp[0][0];
  }
};