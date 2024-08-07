// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
pair<int, int> dir1[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
pair<int, int> dir2[4] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
class neighborSum {
  vector<pair<int, int>> g;
  vector<vector<int>> grid;
  int n;

 public:
  neighborSum(vector<vector<int>>& grid_) {
    grid.swap(grid_);
    n = grid.size();
    int nn = n * n;
    g.resize(nn);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[grid[i][j]] = {i, j};
      }
    }
  }

  int adjacentSum(int value) {
    auto [x, y] = g[value];

    int sum = 0;
    for (auto [i, j] : dir1) {
      int X = x + i;
      int Y = y + j;
      if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
      sum += grid[X][Y];
    }
    return sum;
  }

  int diagonalSum(int value) {
    auto [x, y] = g[value];

    int sum = 0;
    for (auto [i, j] : dir2) {
      int X = x + i;
      int Y = y + j;
      if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
      sum += grid[X][Y];
    }
    return sum;
  }
};

/**
 * Your neighborSum object will be instantiated and called as such:
 * neighborSum* obj = new neighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */