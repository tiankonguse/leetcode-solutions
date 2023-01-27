// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minCost(vector<int>& nums, ll k) {
    int n = nums.size();
    vector<ll> dp(n, INT_MAX);
    dp[0] = 0;

    vector<int> counts(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      fill(counts.begin(), counts.end(), 0);
      int one = 0;
      for (int j = i; j <= n; j++) {
        int v = nums[j - 1];
        counts[v]++;
        if (counts[v] == 1) {
          one++;
        } else if (counts[v] == 2) {
          one--;
        }
        dp[j] = min(dp[j], dp[i - 1] + k + (j - i + 1) - one);
      }
    }
    return dp[n];
  }
};
