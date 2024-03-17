// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  vector<int> nums;
  vector<vector<int>> dp;
  int sum;

  int Dfs(int l, int r) {
    if (l >= r) return 0;
    int& ret = dp[l][r];
    if (ret != -1) return ret;
    ret = 0;

    if (nums[l] + nums[l + 1] == sum) {
      ret = max(ret, 1 + Dfs(l + 2, r));
    }
    if (nums[l] + nums[r] == sum) {
      ret = max(ret, 1 + Dfs(l + 1, r - 1));
    }
    if (nums[r - 1] + nums[r] == sum) {
      ret = max(ret, 1 + Dfs(l, r - 2));
    }

    return ret;
  }

  int Check(int sum) {
    this->sum = sum;
    dp.clear();
    dp.resize(n, vector<int>(n, -1));
    return Dfs(0, n - 1);
  }

 public:
  int maxOperations(vector<int>& nums_) {
    this->nums.swap(nums_);
    n = nums.size();
    int ans = 0;
    ans = max(ans, Check(nums[0] + nums[1]));
    ans = max(ans, Check(nums[0] + nums[n - 1]));
    ans = max(ans, Check(nums[n - 2] + nums[n - 1]));
    return ans;
  }
};