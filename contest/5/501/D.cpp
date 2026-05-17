
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 980 / 999 个通过的测试用例

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const ll INF = (ll)1e12;
typedef pair<ll, ll> pll;
struct Edge {
  ll to, cost;
  Edge(ll to = 0, ll cost = 0) : to(to), cost(cost) {}
};
void Dijkstra(int s, int n, const vector<vector<Edge>>& S, vector<ll>& dist) {
  dist[s] = 0;
  priority_queue<pll, vector<pll>, greater<pll>> pque;
  pque.push({0, s});
  while (!pque.empty()) {
    auto p = pque.top();
    pque.pop();
    ll d = p.first, v = p.second;
    if (dist[v] < d) continue;
    for (const auto& e : S[v]) {
      if (dist[e.to] > dist[v] + e.cost) {
        dist[e.to] = dist[v] + e.cost;
        pque.push({dist[e.to], e.to});
      }
    }
  }
}

class Solution {
 public:
  vector<int> minCost(int n, vector<int>& prices, vector<vector<int>>& roads) {
    vector<vector<Edge>> g(n), rg(n);
    for (auto& r : roads) {
      ll u = r[0], v = r[1], c = r[2], t = r[3];
      g[u].push_back(Edge(v, c));
      g[v].push_back(Edge(u, c));
      rg[v].push_back(Edge(u, c * t));
      rg[u].push_back(Edge(v, c * t));
    }
    vector<vector<ll>> G(n, vector<ll>(n, INF));
    vector<vector<ll>> RG(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) {
      Dijkstra(i, n, g, G[i]);
      Dijkstra(i, n, rg, RG[i]);
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      ll minCost = prices[i];
      for (int j = 0; j < n; j++) {
        ll tmp = prices[j] + G[i][j] + RG[j][i];
        minCost = min(minCost, tmp);
      }
      ans[i] = minCost;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif