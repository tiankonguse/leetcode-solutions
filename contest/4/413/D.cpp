// #include <bits/stdc++.h>

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
  vector<int> maximumSubarrayXor(vector<int>& nums,
                                 vector<vector<int>>& queries) {
    int n = nums.size();
    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, 0));
    vector<vector<ll>> maxLeft(n + 2, vector<ll>(n + 2, 0));
    vector<vector<ll>> maxRange(n + 2, vector<ll>(n + 2, 0));
    for (int i = 0; i < n; i++) {
      dp[i][0] = nums[i];
      maxLeft[i][0] = dp[i][0];
      maxRange[i][i] = dp[i][0];
    }
    for (int i = n - 2; i >= 0; i--) {
      for (int j = 1; j < n - i; j++) {
        dp[i][j] = dp[i][j - 1] ^ dp[i + 1][j - 1];
        maxLeft[i][j] = max(dp[i][j], maxLeft[i][j - 1]);
      }
    }

    for (int i = n - 2; i >= 0; i--) {
      for (int j = 1; j < n - i; j++) {
        maxRange[i][i + j] = max(maxLeft[i][j], maxRange[i + 1][i + j]);
      }
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto& q : queries) {
      int x = q[0], y = q[1];
      ans.push_back(maxRange[x][y]);
    }
    return ans;
  }
};