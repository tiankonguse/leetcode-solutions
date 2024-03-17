// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<pair<int, int>>> g;
  int n;
  int k;  // signalSpeed

  int Dfs(int x, int pre, int preDis) {
    int ans = 0;
    if (preDis == 0) {
      ans++;
    }
    for (auto [y, v] : g[x]) {
      if (y == pre) continue;
      ans += Dfs(y, x, (preDis - v + k) % k);
    }
    return ans;
  }

 public:
  vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges,
                                             int signalSpeed) {
    n = edges.size() + 1;
    k = signalSpeed;
    g.resize(n);
    for (auto& e : edges) {
      int x = e[0], y = e[1], v = e[2];
      g[x].push_back({y, v % k});
      g[y].push_back({x, v % k});
    }

    vector<int> ans(n);
    for (int x = 0; x < n; x++) {
      int sum = 0;
      for(auto [y, v]: g[x]){
        int num = Dfs(y, x, (k - v + k)% k);
        ans[x] += sum * num;
        sum += num;
      }
    }
    return ans;
  }
};