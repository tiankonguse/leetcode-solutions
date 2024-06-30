// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumLength(vector<int>& nums, int k) {
    int n = nums.size();
    if (k == 1) return n;

    int ans = 0;
    vector<int> stat(k, 0);
    vector<vector<int> > dp(k, vector<int>(k, 0));
    for (auto v : nums) {
      v = v % k;
      stat[v]++;

      for (int i = 0; i < k; i++) {
        dp[i][v] = max(dp[i][v], dp[v][i] + 1);
        ans = max(ans, dp[i][v]);
      }

      ans = max(ans, stat[v]);
    }
    return ans;
  }
};