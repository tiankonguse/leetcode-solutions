
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
constexpr int INF = 1 << 30;
typedef pair<int, ll> Edge;
typedef tuple<ll, int, int> tll;  // {cost, s, lableCount}
typedef pair<char, int> pll;      //
ll Dijkstra(int s, int n, vector<vector<Edge>>& g, const string& labels, int k) {
  vector<vector<ll>> dist(n, vector<ll>(k + 1, INF));  // dist[u][lableCount] -> cost
  priority_queue<tll, vector<tll>, greater<tll>> pque;
  dist[s][1] = 0;
  pque.push({0, s, 1});

  ll ret = INF;
  auto Add = [&](int u, ll uCost, ll uCount, int v, ll vCost) {
    if (labels[u] == labels[v] && uCount + 1 > k) return;
    if (v == n - 1) {
      ret = min(ret, uCost + vCost);
      return;
    }
    ll newCost = uCost + vCost;
    ll newCount = labels[u] == labels[v] ? uCount + 1 : 1;
    if (dist[v][newCount] > newCost) {
      dist[v][newCount] = newCost;
      pque.push({newCost, v, newCount});
    }
  };

  while (!pque.empty()) {
    auto [uCost, u, uCount] = pque.top();
    pque.pop();
    if (dist[u][uCount] < uCost) continue;

    for (auto& [v, vCost] : g[u]) {
      Add(u, uCost, uCount, v, vCost);
    }
  }
  return ret;
}
class Solution {
 public:
  int shortestPath(int n, vector<vector<int>>& edges, const string& labels, int k) {  //
    if (n == 1) return 0;
    vector<vector<Edge>> g(n);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      ll w = e[2];
      g[u].push_back({v, w});
    }
    auto ans = Dijkstra(0, n, g, labels, k);
    return ans == INF ? -1 : ans;
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