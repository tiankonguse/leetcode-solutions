
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  vector<vector<pair<ll, ll>>> g;
  int n;
  int k;

  ll ans = 0;
  // [out]: {修正值权重，是否已删除}
  ll Dfs(const int u, const int pre, const ll W) {
    auto& childs = g[u];
    for (auto& [w, v] : childs) {
      if (v == pre) continue;
      w = Dfs(v, u, w);
    }
    if (int(childs.size()) <= k) {  // 不需要删除
      return W;
    }
    sort(childs.begin(), childs.end());
    childs.resize(childs.size() - k);  // 删除 [0, childNum-k)
    for (auto [w, v] : childs) {       //
      ans += w;
    }
    return max(W - childs.back().first, 0ll);
  }

 public:
  ll maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
    this->k = k;
    n = edges.size() + 1;
    g.resize(n);
    ll sum = 0;
    for (auto& e : edges) {
      int u = e[0], v = e[1];
      ll w = e[2];
      g[u].push_back({w,v});
      g[v].push_back({w,u});
      sum += w;
    }
    ans = 0;
    Dfs(0, -1, 0);
    return sum - ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> edges, int k, ll ans) {
  TEST_SMP2(Solution, maximizeSumOfWeights, ans, edges, k);
}

int main() {
  vector<vector<int>> edges;

  edges = {{0, 1, 4}, {0, 2, 2}, {2, 3, 12}, {2, 4, 6}};
  Test(edges, 2, 22);
  edges = {{0, 1, 5},  {1, 2, 10}, {0, 3, 15},
           {3, 4, 20}, {3, 5, 5},  {0, 6, 10}};
  Test(edges, 3, 65);
  edges = {{0, 5, 41}, {0, 4, 9}, {0, 3, 34}, {3, 1, 12}, {3, 2, 23}};
  Test(edges, 1, 64);
  return 0;
}

#endif