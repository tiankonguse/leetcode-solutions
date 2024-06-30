#include "base.h"
// 树的直径，树形DP

// 算法：求出每个节点为子树根时的最长两条路径

// 优化：没必要储存最长的两个路径，只需要储存当前的最长路径，与当前的求和取max，即可求出最长路径

vector<int> D;
vector<vector<int>> E;

int dfs(int u, int fa) {
  int d = 0;
  for (int v : E[u]) {
    if (v == fa) continue;
    d = max(d, dfs(v, u));
    d = max(d, D[u] + D[v] + 1);
    D[u] = max(D[u], D[v] + 1);
  }
  return d;
}

int Solver(vector<vector<int>>& edges) {
  int n = edges.size() + 1;
  E.clear();
  E.resize(n);
  D.resize(n);
  for (auto& e : edges) {
    int u = e[0];
    int v = e[1];
    E[u].push_back(v);
    E[v].push_back(u);
  }
  return dfs(1, 0);
}
