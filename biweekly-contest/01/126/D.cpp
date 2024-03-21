// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
ll dp[101][101][101];
class Solution {
  vector<int> nums;
  int n;

  ll Dfs(int n, int sum, int num) {
    if (sum == 0 && num == 0) {
      return 1;
    }
    if (n < 0 || num == 0) {
      return 0;
    }
    ll& ret = dp[n][sum][num];
    if (ret != -1) return ret;

    ret = 0;
    ret = Dfs(n - 1, sum, num);  // 不选择
    if (nums[n] <= sum) {   // 选择
      ret += Dfs(n - 1, sum - nums[n], num - 1);
    }
    ret %= mod;

    return ret;
  }

 public:
  int sumOfPower(vector<int>& nums_, int k) {
    nums.swap(nums_);
    n = nums.size();
    memset(dp,-1, sizeof(dp));
    ll ans = 0;
    for(int i=1;i<=n;i++){
      ans = (ans + Dfs(n-1, k, i)) % mod;
    }
    return ans;
  }
};