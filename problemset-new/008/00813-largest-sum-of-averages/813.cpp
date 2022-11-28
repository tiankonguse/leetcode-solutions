
#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<double>> dp;
  vector<int> preSum;
  double Dfs(int n, int k) {
    double& ret = dp[n][k];
    if (ret > -1) return ret;

    if (k == 1) {
    //   printf("n=%d k=%d ret=%06f\n", n, k, 1.0 * preSum[n] / n);
      return ret = 1.0 * preSum[n] / n;
    }

    double sum = 0;
    int num = 0;
    for (int i = n; i > k - 1; i--) {
      double tmp = 1.0 * (preSum[n] - preSum[i - 1]) / (n - i + 1);
    //   printf("n=%d k=%d i=%.6f Dfs(%d,%d)\n", n, k, i, tmp, i - 1, k - 1);
      ret = max(ret, tmp + Dfs(i - 1, k - 1));
    }
    // printf("n=%d k=%d ret=%06f\n", n, k, ret);
    return ret;
  }

 public:
  double largestSumOfAverages(vector<int>& nums, int k) {
    int n = nums.size();
    dp.resize(n + 1, vector<double>(k + 1, -1.0));
    dp[0][0] = 0.0;

    int sum = 0;
    preSum.push_back(sum);
    for (auto v : nums) {
      sum += v;
      preSum.push_back(sum);
    }

    double ans = 0.0;
    for (int i = 1; i <= k; i++) {
      ans = max(ans, Dfs(n, i));
    }

    return ans;
  }
};
