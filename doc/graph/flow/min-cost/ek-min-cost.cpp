#include <bits/stdc++.h>

const int N = 5e3 + 5, M = 1e5 + 5;
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
    while (Spfa()) Update(s, t);
    return {maxflow, mincost};
  }

 private:
  void Add(int f, int t, int v, int c) {
    e[++cnt] = (qxx){h[f], t, v, c}, h[f] = cnt;
  }
  bool Spfa() {
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

EkMinCost ekMinCost;

int main() {
  int s, t, n, m;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  ekMinCost.Init(n);
  while (m--) {
    int u, v, w, c;
    scanf("%d%d%d%d", &u, &v, &w, &c);
    ekMinCost.Addedge(u, v, w, c);
  }
  auto [minCost, maxFlow] = ekMinCost.Solver(s, t);
  printf("%d %d\n", minCost, maxFlow);
  return 0;
}
