// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> g;
  vector<pair<int, int>> zeros;
  vector<pair<int, int>> others;
  int zeroNum, otherNum;
  int ans = INT_MAX;
  int Dis(int x0, int y0, int x1, int y1) {
    return abs(x0 - x1) + abs(y0 - y1);
  }
  void Dfs(int now, int sum) {
    if (now == zeroNum) {
      ans = min(ans, sum);
      return;
    }
    auto [x, y] = zeros[now];

    for (auto [X, Y] : others) {
      if (g[X][Y] == 1) continue;

      g[X][Y]--;
      Dfs(now + 1, sum + Dis(x, y, X, Y));
      g[X][Y]++;
    }
  }

 public:
  int minimumMoves(vector<vector<int>>& grid_) {
    g.swap(grid_);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int v = g[i][j];
        if (v == 0) {
          zeros.push_back({i, j});
        } else if (v > 1) {
          others.push_back({i, j});
        }
      }
    }
    zeroNum = zeros.size();
    otherNum = others.size();
    Dfs(0, 0);
    return ans;
  }
};