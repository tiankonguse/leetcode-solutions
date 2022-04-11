
//这个题目如果暴力去做的话，直接djikstra就行了，但是呢这显然行不通啊。
//我得到提示可以使用超级源点来处理。但是呢这里还有一个问题需要解决：不能是同一个城市中的。
//这个问题可以通过什么方法来解决呢？

#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m, k, l;
  cin >> n >> m >> k >> l;
  vector<int> city(n + 1);
  for (int i = 1; i <= n; ++i) cin >> city[i];
  vector<int> popular(l);
  for (auto &v : popular) cin >> v;

  using LL = int64_t;
  vector<vector<pair<int, LL>>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    g[u].emplace_back(v, c);
    g[v].emplace_back(u, c);
  }

  //超级源点0
  for (auto v : popular) {
    g[0].emplace_back(v, 0);
  }

  constexpr LL INF = 1e18;
  vector<vector<LL>> dist(n + 1, vector<LL>(2, INF));
  vector<vector<bool>> vis(n + 1, vector<bool>(2));

  struct Node {
    int u;
    LL d;
    int src;
    Node() {}
    Node(int u_, LL d_, int src_) : u(u_), d(d_), src(src_) {}
  };

  auto cmp = [](const Node &lhs, const Node &rhs) { return lhs.d > rhs.d; };
  priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
  for (auto u : popular) {
    dist[u][0] = 0;
    pq.emplace(u, 0, city[u]);
  }
  while (!pq.empty()) {
    auto [u, d, src] = pq.top();
    pq.pop();
    if (vis[u][city[u] != src]) continue;
    vis[u][city[u] != src] = true;
    for (const auto &[v, c] : g[u]) {
      if (dist[v][city[v] != src] > d + c) {
        dist[v][city[v] != src] = d + c;
        pq.emplace(v, dist[v][city[v] != src], src);
      }
    }
  }

  cout << (dist[1][1] == INF ? -1 : dist[1][1]);
  for (int i = 2; i <= n; ++i)
    cout << " " << (dist[i][1] == INF ? -1 : dist[i][1]);
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
  return 0;
}
