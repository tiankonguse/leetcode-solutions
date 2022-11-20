#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
class Solution {
  ll S;
  vector<vector<int>> g;
  int n;

  // return: people, ans
  pll Dfs(int x, int pre) {
    ll p = 1;
    ll d = 0;

    for (auto y : g[x]) {
      if (y == pre) continue;

      auto [py, dy] = Dfs(y, x);
      p += py;
      d += dy + (py + S - 1) / S;
    }
    return {p, d};
  }

 public:
  ll minimumFuelCost(vector<vector<int>>& roads, int seats) {
    S = seats;
    n = roads.size() + 1;
    g.resize(n);
    for (auto& v : roads) {
      int x = v[0], y = v[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    return Dfs(0, -1).second;
  }
};