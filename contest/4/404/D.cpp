// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> d;
  int c;
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
    d.clear();
    E.clear();
    E.resize(n + 1);
    d.resize(n + 1, 0);
    c = 0;
    for (auto& e : edges) {
      int u = e[0] + 1;
      int v = e[1] + 1;
      E[u].push_back(v);
      E[v].push_back(u);
    }
    dfs(1, 0);
    d[c] = 0;
    dfs(c, 0);
    return d[c];
  }

 public:
  int minimumDiameterAfterMerge(vector<vector<int>>& edges1,
                                vector<vector<int>>& edges2) {
    int a1 = Solver(edges1);
    int a2 = Solver(edges2);
    int a3 = (a1 + 1) / 2 + (a2 + 1) / 2 + 1;
    printf("a1=%d a2=%d a3=%d\n", a1, a2, a3);
    return min(a3, min(a1, a2));
  }
};
