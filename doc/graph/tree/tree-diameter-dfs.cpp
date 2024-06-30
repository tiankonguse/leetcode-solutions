#include "base.h"
// 树的直径， DFS 算法

// 算法：第一遍 DFS 找到的最长深度就是直径的一个端点，第二遍 DFS
// 求出直径的另外一个端点

// 反证法可以证明

int c;
vector<int> d;
vector<vector<int>> E;
void dfs(int u, int fa) {
  for (int v : E[u]) {
    if (v == fa) continue;
    d[v] = d[u] + 1;
    if (d[v] > d[c]) c = v;
    dfs(v, u);
  }
}
int Solver(vector<vector<int>>& edges) {
  int n = edges.size() + 1;
  E.clear();
  E.resize(n);
  d.resize(n, 0);
  c = 0;
  for (auto& e : edges) {
    int u = e[0];
    int v = e[1];
    E[u].push_back(v);
    E[v].push_back(u);
  }
  c = 1; //随便选择一个端点
  d[c] = 0;
  dfs(c, 0);

  d[c] = 0;
  dfs(c, 0);
  return d[c];
}