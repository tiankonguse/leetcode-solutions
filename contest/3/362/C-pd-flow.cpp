// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int N = 11 + 5, M = 100 + 5;
const int INF = 0x3f3f3f3f;

class PrimalDualMinCost {
  struct Edge {
    int v, f, c, next;
  };

  struct Node {
    int v, e;
  };

  Edge e[M];
  Node p[N];
  int head[N], dis[N], vis[N];
  ll h[N];
  int n, s, t, cnt = 1, maxf, minc;

 public:
  void Init(int n) {
    this->n = n;
    cnt = 1;
    memset(head, 0, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    memset(p, 0, sizeof(p));
  }
  void AddEdge(int u, int v, int f, int c) {
    Add(u, v, f, c);
    Add(v, u, 0, -c);
  }
  pair<int, int> Solver(int s, int t) {
    this->s = s;
    this->t = t;
    maxf = 0;
    minc = 0;
    Spfa();  // 先求出初始势能
    while (Dijkstra()) {
      int minf = INF;
      for (int i = 1; i <= n; i++) h[i] += dis[i];
      for (int i = t; i != s; i = p[i].v) minf = min(minf, e[p[i].e].f);
      for (int i = t; i != s; i = p[i].v) {
        e[p[i].e].f -= minf;
        e[p[i].e ^ 1].f += minf;
      }
      maxf += minf;
      minc += minf * h[t];
    }
    return {maxf, minc};
  }

 private:
  void Spfa() {
    queue<int> q;
    for (int i = 1; i <= n; i++) h[i] = INF;
    h[s] = 0, vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = 0;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v;
        if (e[i].f && h[v] > h[u] + e[i].c) {
          h[v] = h[u] + e[i].c;
          if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
          }
        }
      }
    }
  }

  bool Dijkstra() {
    priority_queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push({-0, s});
    while (!q.empty()) {
      int u = q.top().second;
      q.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].v, nc = e[i].c + h[u] - h[v];
        if (e[i].f && dis[v] > dis[u] + nc) {
          dis[v] = dis[u] + nc;
          p[v].v = u;
          p[v].e = i;
          if (!vis[v]) q.push({-dis[v], v});
        }
      }
    }
    return dis[t] != INF;
  }
  void Add(int u, int v, int f, int c) {
    e[++cnt].v = v;
    e[cnt].f = f;
    e[cnt].c = c;
    e[cnt].next = head[u];
    head[u] = cnt;
  }
};
PrimalDualMinCost minCostFlow;

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
    minCostFlow.Init(11);
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