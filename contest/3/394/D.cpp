// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
const ll INF = (ll)1e18;
struct Edge {
  int index;
  int to;
  ll cost;
  Edge(int to_ = 0, ll cost_ = 0, int index_ = 0)
      : to(to_), cost(cost_), index(index_) {}
};
void Dijkstra(int s, int n, vector<vector<Edge>>& g, vector<ll>& dist) {
  min_queue<pll> pque;
  dist[s] = 0;
  pque.push({dist[s], s});
  while (!pque.empty()) {
    auto p = pque.top();
    pque.pop();
    ll from = p.second, d = p.first;
    if (dist[from] < d) continue;
    for (auto& e : g[from]) {
      int to = e.to;
      ll cost = e.cost;
      if (dist[to] > dist[from] + cost) {
        dist[to] = dist[from] + cost;
        pque.push({dist[to], to});
      }
    }
  }
  for (int i = 0; i < n; i++) {
    printf("i=%d cost=%lld\n", i, dist[i]);
  }
}
class Solution {
  vector<vector<Edge>> g;
  vector<bool> ans;
  vector<ll> dist;
  vector<bool> flags;

  void Dfs(int a) {
    if (flags[a]) return;
    flags[a] = true;

    for (auto& e : g[a]) {
      int b = e.to;
      ll cost = e.cost;
      int index = e.index;

      if (dist[b] + cost == dist[a]) {
        ans[index] = true;
        Dfs(b);
      }
    }
  }

 public:
  vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
    g.resize(n);
    for (int i = 0; i < edges.size(); i++) {
      auto& e = edges[i];
      int a = e[0], b = e[1], w = e[2];
      g[a].push_back(Edge{b, w, i});
      g[b].push_back(Edge{a, w, i});
    }
    dist.resize(n, INF);
    Dijkstra(0, n, g, dist);

    ans.resize(edges.size(), false);
    if (dist[n - 1] == INF) {
      return ans;
    }

    flags.resize(n, 0);
    Dfs(n - 1);

    return ans;
  }
};