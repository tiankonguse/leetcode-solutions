
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
const int maxn = 100005;
const int maxn_log = 20;
vector<int> g[maxn];
int f[maxn][maxn_log], dep[maxn];

int Lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
    if (d & (1 << i)) {
      u = f[u][i];
      d = d ^ (1 << i);
    }
  }
  if (u == v) return u;
  for (int i = maxn_log - 1; i >= 0; i--) {
    if (f[u][i] != f[v][i]) {
      u = f[u][i];
      v = f[v][i];
    }
  }
  return f[u][0];
}
class Solution {
  vector<vector<pair<int, ll>>> g;
  vector<vector<pair<ll, ll>>> dis;
  vector<int> dep;
  void DfsRMQ(int u, int pre) {
    for (auto& [v, w] : g[u]) {
      if (v == pre) continue;
      dep[v] = dep[u] + 1;
      dis[v][0] = {u, w};
      for (int i = 1; i < maxn_log; i++) {
        dis[v][i] = dis[dis[v][i - 1].first][i - 1];
        dis[v][i].second += dis[v][i - 1].second;
      }
      DfsRMQ(v, u);
    }
  }
  int Lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int d = dep[u] - dep[v], i = maxn_log - 1; d && i >= 0; i--) {
      if (d & (1 << i)) {
        auto [p, w] = dis[u][i];
        u = p;
        d = d ^ (1 << i);
      }
    }
    if (u == v) return u;
    for (int i = maxn_log - 1; i >= 0; i--) {
      if (dis[u][i].first != dis[v][i].first) {
        u = dis[u][i].first;
        v = dis[v][i].first;
      }
    }
    return dis[u][0].first;
  }

 public:
  vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
    int n = edges.size() + 1;
    g.resize(n);
    dis.resize(n, vector<pair<ll, ll>>(maxn_log, pair<ll, ll>(0, 0)));
    dep.resize(n, 0);
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      ll w = e[2];
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    DfsRMQ(0, -1);
    vector<int> ans;
    ans.reserve(queries.size());
    auto Dis = [&](int u, int v) {  //
      return dis[u][maxn_log - 1].second - dis[v][maxn_log - 1].second;
    };
    for (auto& q : queries) {
      vector<tuple<int, int, int, int>> nums;
      {
        int u0 = q[0], u1 = q[1], u2 = q[2];
        nums.push_back({Lca(u0, u1), u0, u1, u2});
        nums.push_back({Lca(u0, u2), u0, u2, u1});
        nums.push_back({Lca(u1, u2), u1, u2, u0});
      }
      sort(nums.begin(), nums.end(), [&](const tuple<int, int, int, int>& a, const tuple<int, int, int, int>& b) {
        int au = get<0>(a), bu = get<0>(b);
        return dep[au] > dep[bu];
      });
      int u0 = get<1>(nums[0]), u1 = get<2>(nums[0]), u2 = get<3>(nums[0]);
      int u01 = get<0>(nums[0]);
      int u012 = Lca(u01, u2);
      int sum = 0;
      sum += Dis(u0, u01);
      sum += Dis(u1, u01);
      sum += Dis(u01, u012);
      sum += Dis(u2, u012);
      ans.push_back(sum);
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