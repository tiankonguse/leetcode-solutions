// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n, m;
  vector<vector<int>> rowMax;
  vector<vector<int>> colMax;

  void Init() {
    rowMax.resize(n + 1, vector<int>(m + 1, 0));
    colMax.resize(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        rowMax[i][j] = j;
        colMax[i][j] = i;
      }
    }
  }
  void Update(int x, int y) {
    rowMax[x][y] = max(FindRow(x, y), FindRow(x, y + 1));
    colMax[x][y] = max(FindCol(x, y), FindCol(x + 1, y));
  }
  int FindRow(int x, int y) {
    if (y != rowMax[x][y]) {
      rowMax[x][y] = max(rowMax[x][y], FindRow(x, rowMax[x][y]));
    }
    return rowMax[x][y];
  }
  int FindCol(int x, int y) {
    if (x != colMax[x][y]) {
      colMax[x][y] = max(colMax[x][y], FindCol(colMax[x][y], y));
    }
    return colMax[x][y];
  }

 public:
  int minimumVisitedCells(const vector<vector<int>>& grid) {
    n = grid.size();
    m = grid.front().size();

    vector<vector<int>> ans(n, vector<int>(m, -1));

    Init();

    queue<pair<int, int>> que;
    ans[0][0] = 1;
    que.push({0, 0});
    Update(0, 0);

    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();

      for (int Y = FindRow(x, y); Y < m && Y <= y + grid[x][y];
           Y = max(Y + 1, FindRow(x, Y))) {
        const int X = x;
        Update(X, Y);
        if (ans[X][Y] != -1) continue;
        que.push({X, Y});
        ans[X][Y] = ans[x][y] + 1;
      }

      for (int X = FindCol(x, y); X < n && X <= x + grid[x][y];
           X = max(X + 1, FindCol(X, y))) {
        const int Y = y;
        Update(X, Y);
        if (ans[X][Y] != -1) continue;
        que.push({X, Y});
        ans[X][Y] = ans[x][y] + 1;
      }
    }
    return ans.back().back();
  }
};