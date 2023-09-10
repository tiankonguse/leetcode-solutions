// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int N = 11 + 5, M = 100 + 5;
const int INF = 0x3f3f3f3f;

class DinicMinCost {
  int n;
  int minCost, maxFlow;
  int tot = 1;
  int lnk[N], cur[N], dis[N];
  int ter[M], nxt[M], cap[M], cost[M];
  bool vis[N];

 public:
  void Init(int n_) {
    n = n_;
    tot = 1;
    memset(vis, 0, sizeof(vis));
    memset(lnk, 0, sizeof(lnk));
  }
  void Addedge(int u, int v, int w, int c) {
    Add(u, v, w, c), Add(v, u, 0, -c);
  }

  pair<int, int> MCMF(int s, int t) {
    minCost = 0;
    maxFlow = 0;
    while (Spfa(s, t)) {
      int x;
      while ((x = Dfs(s, t, INF))) minCost += x;
    }
    return {minCost, maxFlow};
  }

 private:
  void Add(int u, int v, int w, int c) {
    ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w,
    cost[tot] = c;
  }
  bool Spfa(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    memcpy(cur, lnk, sizeof(lnk));
    std::queue<int> q;
    q.push(s), dis[s] = 0, vis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = 0;
      for (int i = lnk[u]; i; i = nxt[i]) {
        int v = ter[i];
        if (cap[i] && dis[v] > dis[u] + cost[i]) {
          dis[v] = dis[u] + cost[i];
          if (!vis[v]) q.push(v), vis[v] = 1;
        }
      }
    }
    return dis[t] != INF;
  }
  int Dfs(int u, int t, int flow) {
    if (u == t) return flow;
    vis[u] = 1;
    int ans = 0;
    for (int& i = cur[u]; i && ans < flow; i = nxt[i]) {
      int v = ter[i];
      if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
        int x = Dfs(v, t, std::min(cap[i], flow - ans));
        if (x) maxFlow += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
      }
    }
    vis[u] = 0;
    return ans;
  }
};
DinicMinCost dinicMinCost;

class Solution {
  vector<pair<int, int>> from;
  vector<pair<int, int>> to;
  int Dis(int x0, int y0, int x1, int y1) {
    return abs(x0 - x1) + abs(y0 - y1);
  }
  int H(int x, int y) { return x * 3 + y + 1; }

 public:
  int minimumMoves(vector<vector<int>>& g) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int v = g[i][j];
        if (v == 0) {
          to.push_back({i, j});
        } else if (v > 1) {
          from.push_back({i, j});
        }
      }
    }

    if (from.size() == 0) return 0;
    dinicMinCost.Init(11);
    for (auto [x0, y0] : from) {
      for (auto [x1, y1] : to) {
        int s = H(x0, y0);
        int t = H(x1, y1);
        dinicMinCost.Addedge(s, t, 1, Dis(x0, y0, x1, y1));
      }
    }
    for (auto [x0, y0] : from) {
      int s = H(x0, y0);
      dinicMinCost.Addedge(0, s, g[x0][y0]-1, 0);
    }
    for (auto [x1, y1] : to) {
      int t = H(x1, y1);
      dinicMinCost.Addedge(t, 10, 1, 0);
    }

    return dinicMinCost.MCMF(0, 10).second;
  }
};