// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxScore(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid.front().size();
    int ans = grid.back().back() - grid.front().front();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int tmp = grid[i][j];
        if (j != 0) {
          ans = max(ans, grid[i][j] - grid[i][j - 1]);
          tmp = min(tmp, grid[i][j - 1]);
        }
        if (i != 0) {
          ans = max(ans, grid[i][j] - grid[i - 1][j]);
          tmp = min(tmp, grid[i - 1][j]);
        }
        grid[i][j] = tmp;
      }
    }
    return ans;
  }
};