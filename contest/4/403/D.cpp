// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int pre[33][33];
  int n, m;
  int ans;
  void Init() {
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int v = grid[i - 1][j - 1];
        pre[i][j] = v + pre[i][j - 1] + pre[i - 1][j] - pre[i - 1][j - 1];
      }
    }
  }
  int Solver(int x0, int y0, int x1, int y1) {
    int top = 1000;
    int down = 0;
    int left = 1000;
    int right = 0;

    printf("x=[%d, %d] y=[%d %d] \n", x0, x1, y0, y1);
    for (int i = x0; i <= x1; i++) {
      for (int j = y0; j <= y1; j++) {
        if (grid[i][j]) {
          top = min(top, i);
          down = max(down, i);
          left = min(left, j);
          right = max(right, j);
        }
      }
    }
    return (down - top + 1) * (right - left + 1);
  }
  void Solver() {
    printf("n=%d m=%d \n", n, m);
    // 枚举行
    for (int i = 1; i < n; i++) {
      // [1,i]  [i+1, n]
      int up = pre[i][m];
      int down = pre[n][m] - pre[i][m];
      if (up == 0 || down == 0) continue;

      // 先枚举行，在 [1,i] 里拆分
      for (int j = 1; j < i; j++) {
        // [1, 1] [j, m]
        // [j+1, 1] [i, m]
        // [i+1, 1] [n, m]

        int up = pre[j][m];
        int mid = pre[i][m] - pre[j][m];
        if (up == 0 || mid == 0) continue;

        int tmp = 0;
        tmp += Solver(0, 0, j - 1, m - 1);
        tmp += Solver(j, 0, i - 1, m - 1);
        tmp += Solver(i, 0, n - 1, m - 1);
        ans = min(ans, tmp);
      }

      // 再枚举列，在 [1,m] 里拆分
      for (int j = 1; j < m; j++) {
        // [1,1] [i, j]
        // [1,j+1] [i,m]
        // [i+1, 1] [n, m]
        int left = pre[i][j];
        int right = pre[i][m] - pre[i][j];
        if (left == 0 || right == 0) continue;

        int tmp = 0;
        tmp += Solver(0, 0, i - 1, j - 1);
        tmp += Solver(0, j, i - 1, m - 1);
        tmp += Solver(i, 0, n - 1, m - 1);
        ans = min(ans, tmp);
      }
    }
  }

  void trans() {
    n = grid.size();
    m = grid.front().size();
    vector<vector<int>> tmp(m, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        tmp[j][n - 1 - i] = grid[i][j];
      }
    }

    grid = tmp;
    n = grid.size();
    m = grid.front().size();
  }

  vector<vector<int>> grid;

 public:
  int minimumSum(vector<vector<int>>& grid_) {
    grid.swap(grid_);
    ans = INT_MAX;
    for (int i = 0; i < 4; i++) {
      trans();
      Init();
      Solver();
    }
    return ans;
  }
};