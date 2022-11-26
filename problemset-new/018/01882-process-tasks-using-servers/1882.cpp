#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
    int m = edges.size();
    vector<vector<int>> g(n);
    vector<pair<ll, ll>> lrCost(m);
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i][0], v = edges[i][1], c = edges[i][2];
      g[u].push_back(i);
      g[v].push_back(i);
      lrCost[i] = {0, 0};
    }

    vector<ll> flag(n, -1);

    ll ans = 1;
    flag[0] = maxMoves;

    while (true) {
      int maxPos = -1;
      ll maxLeftStep = 0;
      for (int i = 0; i < n; i++) {
        if (flag[i] > maxLeftStep) {
          maxLeftStep = flag[i];
          maxPos = i;
        }
      }

      if (maxPos == -1) break;
      flag[maxPos] = -2;  // 代表处理过了
      for (auto i : g[maxPos]) {
        int u = 0, v = 0;
        ll c = 0;
        ll* puc = nullptr;
        ll* pvc = nullptr;

        bool goNext = false;

        if (maxPos == edges[i][0]) {
          u = edges[i][0], v = edges[i][1], c = edges[i][2];
          auto& [uc, vc] = lrCost[i];
          puc = &uc;
          pvc = &vc;
        } else {
          v = edges[i][0], u = edges[i][1], c = edges[i][2];
          auto& [vc, uc] = lrCost[i];
          puc = &uc;
          pvc = &vc;
        }

        ll& uc = *puc;
        ll& vc = *pvc;

        if (vc == 0) {
          uc = min(c, maxLeftStep);
          ans += uc;
        } else {
          uc = min(c - vc, maxLeftStep);
          ans += uc;
        }

        if (c < maxLeftStep) {
          if (flag[v] == -2) continue;  // 处理过了
          if (flag[v] == -1) ans++;     // 首次到达
          flag[v] = max(flag[v], maxLeftStep - c - 1);
        }
      }
    }
    return ans;
  }
};
