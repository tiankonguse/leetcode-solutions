// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  vector<vector<ll>> dp;
  vector<vector<int>> types;
  ll Dfs(int n, int t) {
    ll& ret = dp[n][t];
    if (ret != -1) return ret;

    int C = types[n - 1][0];
    int M = types[n - 1][1];

    ret = 0;
    for (int i = 0; i <= C && i * M <= t; i++) {
      ret = (ret + Dfs(n - 1, t - i * M)) % mod;
    }

    return ret;
  }

 public:
  int waysToReachTarget(int target, vector<vector<int>>& types_) {
    types.swap(types_);
    int n = types.size();
    dp.resize(n + 1, vector<ll>(target + 1, -1));

    dp[0][0] = 1;
    for (int i = 1; i <= target; i++) dp[0][i] = 0;
    return Dfs(n, target);
  }
};
