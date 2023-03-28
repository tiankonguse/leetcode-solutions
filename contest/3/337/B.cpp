// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool checkValidGrid(vector<vector<int>>& grid) {
    int n = grid.size();
    int x = 0, y = 0;
    int N = n * n, index = 1;
    int dir[8][2] = {{1, 2},  {1, -2},  {2, 1},  {2, -1},
                     {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
    while (index < N) {
      bool flag = false;
      for (int i = 0; i < 8; i++) {
        int X = x + dir[i][0];
        int Y = y + dir[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
        if (grid[X][Y] == index) {
          x = X;
          y = Y;
          flag = true;
          break;
        }
      }
      if (!flag) return false;
      index++;
    }
    return true;
  }
};

int main() {
  bool ans;
  vector<vector<int>> grid;

  ans = true;
  grid = {{0, 11, 16, 5, 20},
          {17, 4, 19, 10, 15},
          {12, 1, 8, 21, 6},
          {3, 18, 23, 14, 9},
          {24, 13, 2, 7, 22}};

  TEST_SMP1(Solution, checkValidGrid, ans, grid);

  return 0;
}