// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  vector<vector<ll>> dp;
  vector<int> nums;
  int n;

  ll Dfs(int p, int mask) {
    ll& ret = dp[p][mask];
    if (ret != -1) {
      return ret;
    }
    ret = 0;

    if (mask == 0) {
      return ret = 1;
    }

    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) == 0) continue;  //
      if (nums[p] % nums[i] == 0 || nums[i] % nums[p] == 0) {
        ret += Dfs(i, mask ^ (1 << i));
        ret %= mod;
      }
    }

    return ret;
  }

 public:
  int specialPerm(vector<int>& nums_) {
    nums.swap(nums_);
    n = nums.size();
    dp.resize(n, vector<ll>(1 << n, -1));

    ll ans = 0;
    ll MASK = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
      ans += Dfs(i, MASK ^ (1 << i));
      ans %= mod;
    }
    return ans;
  }
};
