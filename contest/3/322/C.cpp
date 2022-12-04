#include <bits/stdc++.h>

#include "base.h"
using namespace std;

constexpr int INF = 1 << 30;
typedef long long ll;
typedef pair<ll, ll> pll;
ll Solver(int s, int t, int n, vector<vector<pll>> &g) {
  ll ans = INF;

  vector<ll> flag(n, false);
  queue<int> que;
  que.push(s);
  flag[s] = true;

  while (!que.empty()) {
    int a = que.front();
    que.pop();
    for (auto [b, c] : g[a]) {
      ans = min(c, ans);
      if (flag[b]) continue;
      flag[b] = true;
      que.push(b);
    }
  }

  return ans;
}
class Solution {
 public:
  int minScore(int n, vector<vector<int>> &roads) {
    vector<vector<pll>> g;
    g.resize(n + 1);
    for (auto &v : roads) {
      ll a = v[0], b = v[1];
      ll c = v[2];
      g[a].push_back({b, c});
      g[b].push_back({a, c});
    }
    return Solver(1, n, n + 1, g);
  }
};