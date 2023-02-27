// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int R = 0, D = 1;
class Solution {
  int n;
  int H(int x, int y) { return x * n + y; }
  pair<int, int> h(int s) { return {s / n, s % n}; }

 public:
  int minimumMoves(vector<vector<int>>& grid) {
    n = grid.size();
    vector<vector<int>> dp(2, vector<int>(n * n, -1));

    queue<pair<int, int>> que;
    int s = H(0, 1);
    que.push({R, s});
    dp[R][s] = 0;

    int X, Y, S;

    while (!que.empty()) {
      auto [dir, s] = que.front();
      que.pop();
      auto [x, y] = h(s);

      if (dir == R) {
        // 朝右
        X = x, Y = y + 1;
        S = H(X, Y);
        if (Y < n && grid[X][Y] == 0 && dp[dir][S] == -1) {
          que.push({dir, S});
          dp[dir][S] = dp[dir][s] + 1;
        }

        //朝下
        X = x + 1, Y = y;
        S = H(X, Y);
        if (X < n && grid[X][Y] == 0 && grid[X][Y - 1] == 0 &&
            dp[dir][S] == -1) {
          que.push({dir, S});
          dp[dir][S] = dp[dir][s] + 1;
        }

        // 朝下旋转
        X = x + 1, Y = y - 1;
        S = H(X, Y);
        if (X < n && Y >= 0 && grid[X][Y] == 0 && grid[X][Y + 1] == 0 &&
            dp[1 - dir][S] == -1) {
          que.push({1 - dir, S});
          dp[1 - dir][S] = dp[dir][s] + 1;
        }

      } else {
        // 朝下移动
        X = x + 1, Y = y;
        S = H(X, Y);
        if (X < n && grid[X][Y] == 0 && dp[dir][S] == -1) {
          que.push({dir, S});
          dp[dir][S] = dp[dir][s] + 1;
        }

        // 朝右平移
        X = x, Y = y + 1;
        S = H(X, Y);
        if (Y < n && grid[X][Y] == 0 && grid[X - 1][Y] == 0 &&
            dp[dir][S] == -1) {
          que.push({dir, S});
          dp[dir][S] = dp[dir][s] + 1;
        }

        // 朝右旋转
        X = x - 1, Y = y + 1;
        S = H(X, Y);
        if (X >= 0 && Y < n && grid[X][Y] == 0 && grid[X + 1][Y] == 0 &&
            dp[1 - dir][S] == -1) {
          que.push({1 - dir, S});
          dp[1 - dir][S] = dp[dir][s] + 1;
        }
      }
    }

    return dp[R][H(n - 1, n - 1)];
  }
};