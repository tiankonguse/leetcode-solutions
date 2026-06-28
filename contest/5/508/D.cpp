
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
const ll kMaxTime = 1e13;
constexpr ll INFL = 1LL << 60;
typedef tuple<ll, ll, ll> tll;  // {uTime, s, uPower}
class Solution {
  vector<vector<pair<ll, ll>>> g;  // u->[v, t]
  vector<int> costPower;
  int n;

  pair<ll, ll> Dijkstra(int u, int target, ll maxPower) {
    vector<vector<ll>> dist(n, vector<ll>(maxPower + 1, INFL));
    priority_queue<tll, vector<tll>, greater<tll>> pque;
    dist[u][maxPower] = 0;
    pque.push({0, u, maxPower});

    ll retTime = INFL;
    ll retPower = -1;

    auto Add = [&](int u, ll uTime, ll uPower, int v, ll vTime) {
      // u -> v
      const ll cost = costPower[u];
      if (uPower < cost) return;  // 无法到达
      ll newTime = uTime + vTime;
      ll newPower = uPower - cost;
      if (v == target) {
        if (newTime < retTime) {
          retTime = newTime;
          retPower = newPower;
        } else if (newTime == retTime && newPower > retPower) {
          retPower = newPower;
        }
        return;
      }
      if (dist[v][newPower] > newTime) {
        dist[v][newPower] = newTime;
        pque.push({newTime, v, newPower});
      }
    };
    while (!pque.empty()) {
      auto [uTime, u, uPower] = pque.top();
      pque.pop();
      if (dist[u][uPower] < uTime) continue;
      for (auto& [v, vTime] : g[u]) {
        Add(u, uTime, uPower, v, vTime);
      }
    }
    if (retTime == INFL) {
      return {-1, -1};
    }
    return {retTime, retPower};
  }

 public:
  vector<ll> minTimeMaxPower(int n, vector<vector<int>>& edges, int power, vector<int>& cost_, int source,
                             int target) {  //
    this->n = n;
    costPower.swap(cost_);
    g.resize(n);
    if (source == target) {
      return {0, power};
    }
    for (auto& e : edges) {
      ll u = e[0], v = e[1], t = e[2];
      g[u].push_back({v, t});
    }
    auto ret = Dijkstra(source, target, power);
    if (ret.first == -1) {
      return {-1, -1};
    }
    return {ret.first, ret.second};
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