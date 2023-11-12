// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  vector<int> coins;
  vector<vector<ll>> dp;
  const int MAX_LEV = 31;
  const int INIT_VAL = INT_MIN;
  ll K;

  ll Dfs(int u, int pre, int lev) {
    lev = min(lev, MAX_LEV);
    ll& ret = dp[u][lev];
    if (ret != INIT_VAL) {
      return ret;
    }
    ll val = coins[u] >> lev;

    ll ans1 = val - K;
    for (auto v : g[u]) {
      if (v == pre) continue;
      ans1 += Dfs(v, u, lev);
    }

    ll ans2 = val / 2;
    for (auto v : g[u]) {
      if (v == pre) continue;
      ans2 += Dfs(v, u, lev + 1);
    }
    return ret = max(ans1, ans2);
  }

 public:
  int maximumPoints(vector<vector<int>>& edges, vector<int>& coins_, int K_) {
    K = K_;
    coins.swap(coins_);

    int n = coins.size();
    g.resize(n);
    for (auto& e : edges) {
      int u = e[0];
      int v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }
    dp.resize(n, vector<ll>(MAX_LEV + 1, INIT_VAL));
    return Dfs(0, -1, 0);
  }
};
