#include <bits/stdc++.h>

const int N = 5e3 + 5, M = 1e5 + 5;
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

  pair<int, int> Solver(int s, int t) {
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
    for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
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

int main() {
  int s, t, n, m;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  dinicMinCost.Init(n);
  while (m--) {
    int u, v, w, c;
    scanf("%d%d%d%d", &u, &v, &w, &c);
    dinicMinCost.Addedge(u, v, w, c);
  }
  auto [minCost, maxFlow] = dinicMinCost.Solver(s, t);
  printf("%d %d\n", minCost, maxFlow);
  return 0;
}
