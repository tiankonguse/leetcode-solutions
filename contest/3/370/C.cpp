// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  vector<vector<int>> g;
  vector<vector<ll>> dp;
  vector<int> values;

  bool IsLeaf(int u, int p) {  // 是否是叶子
    return g[u].size() == 1 && g[u].front() == p;
  }

  ll Dfs(int u, int p, int flag) {
    ll& ret = dp[flag][u];
    if (ret != -1) {
      return ret;
    }
    ret = 0;

    // 是叶子
    if (IsLeaf(u, p)) {
      if (flag) {
        ret = values[u];
      }
      return ret;
    }

    // 父节点已经选择
    if (flag) {
      ret = values[u];
      for (auto v : g[u]) {
        if (v == p) {
          continue;
        }
        ret += Dfs(v, u, 1);
      }
      return ret;
    }

    // 父节点没有选择，当前节点保留
    ll ans1 = 0;
    for (auto v : g[u]) {
      if (v == p) {
        continue;
      }
      ans1 += Dfs(v, u, 1);
    }

    //  父节点没有选择，当前节点拿走
    ll ans2 = values[u];
    for (auto v : g[u]) {
      if (v == p) {
        continue;
      }
      ans2 += Dfs(v, u, 0);
    }

    return ret = max(ans1, ans2);
  }

 public:
  long long maximumScoreAfterOperations(vector<vector<int>>& edges,
                                        vector<int>& values_) {
    values.swap(values_);
    n = values.size();

    g.resize(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      g[u].push_back(v);
      g[v].push_back(u);
    }

    dp.resize(2, vector<ll>(n, -1));
    return Dfs(0, -1, 0);
  }
};