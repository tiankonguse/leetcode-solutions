// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  vector<vector<int>> g;
  set<pair<int, int>> h;

  int DfsBase(int a, int pre) {
    int num = 0;
    for (auto b : g[a]) {
      if (b == pre) continue;
      if (h.count({a, b})) num++;
      num += DfsBase(b, a);
    }
    return num;
  }
  int K;
  int Dfs(int a, int pre, int num) {
    int ans = 0;
    if (h.count({pre, a})) num--;
    if (h.count({a, pre})) num++;
    if (num >= K) ans++;

    for (auto b : g[a]) {
      if (b == pre) continue;
      ans += Dfs(b, a, num);
    }
    return ans;
  }

 public:
  int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses,
                int k) {
    K = k;
    n = edges.size() + 1;
    g.resize(n);
    for (auto& v : edges) {
      int a = v[0], b = v[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }

    for (auto& v : guesses) {
      int a = v[0], b = v[1];
      h.insert({a, b});
    }

    int num = DfsBase(0, -1);
    return Dfs(0, -1, num);
  }
};