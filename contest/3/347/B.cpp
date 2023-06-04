// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid.front().size();
    vector<vector<int>> topLeft(n, vector<int>(m, 0));
    vector<vector<int>> bottomRight(n, vector<int>(m, 0));
    unordered_set<int> cols;

    // topLeft 上面的答案
    for (int i = 0; i < m; i++) {
      cols.clear();
      int x = 0, y = i;
      while (x < n && y < m) {
        topLeft[x][y] = cols.size();
        cols.insert(grid[x][y]);
        x++, y++;
      }
    }

    // topLeft 左边的答案
    for (int i = 0; i < n; i++) {
      cols.clear();
      int x = i, y = 0;
      while (x < n && y < m) {
        topLeft[x][y] = cols.size();
        cols.insert(grid[x][y]);
        x++, y++;
      }
    }

    // bottomRight 右边的答案
    for (int i = 0; i < n; i++) {
      cols.clear();
      int x = i, y = m - 1;
      while (x >= 0 && y >= 0) {
        bottomRight[x][y] = cols.size();
        cols.insert(grid[x][y]);
        x--, y--;
      }
    }

    // bottomRight 下面的答案
    for (int i = 0; i < m; i++) {
      cols.clear();
      int x = n - 1, y = i;
      while (x >= 0 && y >= 0) {
        bottomRight[x][y] = cols.size();
        cols.insert(grid[x][y]);
        x--, y--;
      }
    }

    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans[i][j] = abs(topLeft[i][j] - bottomRight[i][j]);
      }
    }
    return ans;
  }
};