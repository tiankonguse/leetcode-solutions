// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  vector<int> price;
  vector<int> dep;
  vector<int> nums;
  vector<int> fa;
  vector<vector<int>> dp;

  void DfsDep(int s, int pre, int preDep) {
    dep[s] = preDep + 1;
    fa[s] = pre;
    for (auto t : g[s]) {
      if (t == pre) continue;
      DfsDep(t, s, dep[s]);
    }
  }

  int Dfs(int s, int pre, int preUse) {
    int& ret = dp[preUse][s];
    if (ret != -1) {
      return ret;
    }
    // printf("s=%d pre=%d preUse=%d\n", s, pre, preUse);
    ret = INT_MAX;

    // 当前可以使用
    if (preUse == 0) {
      int tmp = price[s] * nums[s] / 2;
      for (auto t : g[s]) {
        if(t == pre) continue;
        tmp += Dfs(t, s, 1);
      }
      ret = min(ret, tmp);
    }

    // 当前不使用
    {
      int tmp = price[s] * nums[s];
      for (auto t : g[s]) {
        if(t == pre) continue;
        tmp += Dfs(t, s, 0);
      }
      ret = min(ret, tmp);
    }
    return ret;
  }

 public:
  int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price_,
                        vector<vector<int>>& trips) {
    price.swap(price_);
    g.resize(n);
    dep.resize(n, -1);
    nums.resize(n, 0);
    fa.resize(n, -1);
    dp.resize(2, vector<int>(n, -1));

    for (auto& v : edges) {
      int a = v[0], b = v[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }

    DfsDep(0, -1, -1);

    for (auto& p : trips) {
      int a = p[0], b = p[1];
      while (a != b) {
        if (dep[a] > dep[b]) {
          nums[a]++;
          a = fa[a];
        } else if (dep[a] < dep[b]) {
          nums[b]++;
          b = fa[b];
        } else {
          nums[a]++;
          nums[b]++;
          a = fa[a];
          b = fa[b];
        }
      }
      nums[a]++;
    }

    return Dfs(0, -1, 0);
  }
};