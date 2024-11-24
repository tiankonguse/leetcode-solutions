
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
  vector<vector<pair<int, ll>>> g;
  int n;
  int k;

  ll ans = 0;
  // [out]: {修正值权重，是否已删除}
  pair<ll, bool> Dfs(const int u, const int pre, const ll W) {
    vector<pair<ll, int>> childs;
    childs.reserve(g[u].size());
    for (const auto& [v, w] : g[u]) {
      if (v == pre) continue;
      auto [ret_w, ret_flag] = Dfs(v, u, w);
      if (!ret_flag) {
        childs.push_back({ret_w, v});
      }
    }
    int childNum = childs.size();
    if (pre != -1) {
      childs.push_back({W, pre});
      childNum++;
    }

    if (childNum <= k) {  // 不需要删除
      return {W, false};
    }
    sort(childs.begin(), childs.end());
    // 删除 [0, childNum-k)
    bool flag = false;
    int lastVal = childs[0].first;
    for (int i = 0; i + k < childNum; i++) {  //
      auto [w, v] = childs[i];
      ans += w;
      if (v == pre) {
        flag = true;
      }
      lastVal = w;
    }
    if (flag) {
      return {W, true};
    } else {
      return {W - lastVal, false};
    }
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
      g[u].push_back({v, w});
      g[v].push_back({u, w});
      sum += w;
    }
    ans = 0;
    Dfs(0, -1, INT_MAX);
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