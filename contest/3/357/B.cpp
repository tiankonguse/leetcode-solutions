// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> sum;
  vector<vector<int>> dp;
  int m;
  int Dfs(int l, int r) {
    int& ret = dp[l][r];
    if (ret != -1) return ret;
    if (l == r) return ret = 1;
    if (sum[r] - sum[l - 1] < m) return false;

    for (int i = l; i < r; i++) {  // [l, i][i+1, r]
      if (Dfs(l, i) && Dfs(i + 1, r)) {
        return ret = 1;
      }
    }
    return ret = 0;
  };

 public:
  bool canSplitArray(vector<int>& nums, int m_) {
    m = m_;
    int n = nums.size();
    if (n == 1 || n == 2) return true;
    sum.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + nums[i - 1];
    }
    dp.resize(n + 1, vector<int>(n + 1, -1));
    return Dfs(1, n);
  }
};
