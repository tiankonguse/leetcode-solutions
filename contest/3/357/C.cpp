// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;
class Solution {
  int n;
  vector<vector<int>> dis;
  vector<vector<int>> grid;

  void InitDis() {
    dis.resize(n, vector<int>(n, -1));

    queue<pair<int, int>> que;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          dis[i][j] = 0;
          que.push({i, j});
        }
      }
    }
    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
        if (dis[X][Y] != -1) continue;
        dis[X][Y] = dis[x][y] + 1;
        que.push({X, Y});
      }
    }
  }

 public:
  int maximumSafenessFactor(vector<vector<int>>& grid_) {
    grid.swap(grid_);
    n = grid.size();
    InitDis();
    if (n == 1) return dis[0][0];

    max_queue<tuple<int, int, int>> que;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
    que.push({dis[0][0], 0, 0});
    dp[0][0] = dis[0][0];

    while (!que.empty()) {
      auto [d, x, y] = que.top();
      que.pop();

      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
        if (dp[X][Y] != INT_MAX) continue;
        dp[X][Y] = min(dis[X][Y], dp[x][y]);
        que.push({dp[X][Y], X, Y});
        if (X == n - 1 && Y == n - 1) return dp[X][Y];
      }
    }

    return 0;
  }
};
