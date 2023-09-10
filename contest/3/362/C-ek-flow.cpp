// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int N = 11 + 5, M = 100 + 5;
const int INF = 0x3f3f3f3f;

class EkMinCost {
  struct qxx {
    int nex, t, v, c;
  };
  qxx e[M];
  int h[N], cnt = 1;
  int dis[N], pre[N], incf[N];
  bool vis[N];
  int maxflow, mincost;

 public:
  void Init() {
    cnt = 1;
    memset(h, 0, sizeof(h));
    memset(pre, 0, sizeof(pre));
    memset(incf, 0, sizeof(incf));
    memset(vis, 0, sizeof(vis));
  }
  void AddEdge(int f, int t, int v, int c) {
    Add(f, t, v, c);
    Add(t, f, 0, -c);
  }
  pair<int, int> Solver(int s, int t) {
    maxflow = 0;
    mincost = 0;
    while (Spfa(s, t)) Update(s, t);
    return {maxflow, mincost};
  }

 private:
  void Add(int f, int t, int v, int c) {
    e[++cnt] = (qxx){h[f], t, v, c}, h[f] = cnt;
  }
  bool Spfa(int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    queue<int> q;
    q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
    while (q.size()) {
      int u = q.front();
      q.pop();
      vis[u] = 0;
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
        if (!w || dis[v] <= dis[u] + c) continue;
        dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
        if (!vis[v]) q.push(v), vis[v] = 1;
      }
    }
    return incf[t];
  }
  void Update(int s, int t) {
    maxflow += incf[t];
    for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
      e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
      mincost += incf[t] * e[pre[u]].c;
    }
  }
};

EkMinCost minCostFlow;

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
    minCostFlow.Init();
    for (auto [x0, y0] : from) {
      for (auto [x1, y1] : to) {
        int s = H(x0, y0);
        int t = H(x1, y1);
        minCostFlow.AddEdge(s, t, 1, Dis(x0, y0, x1, y1));
      }
    }
    for (auto [x0, y0] : from) {
      int s = H(x0, y0);
      minCostFlow.AddEdge(0, s, g[x0][y0] - 1, 0);
    }
    for (auto [x1, y1] : to) {
      int t = H(x1, y1);
      minCostFlow.AddEdge(t, 10, 1, 0);
    }

    return minCostFlow.Solver(0, 10).second;
  }
};