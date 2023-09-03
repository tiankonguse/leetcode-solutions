// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int maxn = 100005;
const int maxn_log = 20;
vector<pair<int, int>> g[maxn];
int f[maxn][maxn_log], dep[maxn];
vector<int> F[maxn];

void InitRMQ(int n) {
  for (int i = 0; i < n; i++) {
    g[i].clear();
    dep[i] = 0;
    for (int j = 0; j < maxn_log; j++) {
      f[i][j] = 0;
    }
    F[i].clear();
    F[i].resize(27, 0);
  }
}

void DfsRMQ(int u, int pre) {
  for (auto [v, w] : g[u]) {
    if (v == pre) continue;
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    dep[v] = dep[u] + 1;
    f[v][0] = u;
    F[v] = F[u];
    F[v][w]++;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第
    // 2^(i-1) 的祖先节点。
    for (int i = 1; i < maxn_log; i++) {
      f[v][i] = f[f[v][i - 1]][i - 1];
    }
    DfsRMQ(v, u);
  }
}

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
 public:
  vector<int> minOperationsQueries(int n, vector<vector<int>>& edges,
                                   vector<vector<int>>& queries) {
    InitRMQ(n);
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i][0];
      int v = edges[i][1];
      int w = edges[i][2];
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    DfsRMQ(0, -1);

    vector<int> ans;
    int q = queries.size();
    ans.reserve(q);
    for (auto& v : queries) {
      int a = v[0], b = v[1];
      int c = Lca(a, b);
      vector<int> nums(27, 0);
      for (int i = 0; i < 27; i++) {
        nums[i] += F[a][i] - F[c][i];
        nums[i] += F[b][i] - F[c][i];
      }
      int sum = 0;
      int maxNum = 0;
      for (int i = 0; i < 27; i++) {
        sum += nums[i];
        maxNum = max(maxNum, nums[i]);
      }
      ans.push_back(sum - maxNum);
    }
    return ans;
  }
};
