#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

const int N = 5e3 + 5, M = 1e5 + 5;
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
PrimalDualMinCost flow;

int main() {
  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  flow.Init(n);
  for (int i = 1; i <= m; i++) {
    int u, v, f, c;
    scanf("%d%d%d%d", &u, &v, &f, &c);
    flow.AddEdge(u, v, f, c);
  }
  auto [maxf, minc] = flow.Solver(s, t);

  printf("%d %d\n", maxf, minc);
  return 0;
}
