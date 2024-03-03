// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int countSubmatrices(vector<vector<int>>& grid, int k) {
    int n = grid.size();
    int m = grid.front().size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (i > 0) {
        grid[i][0] += grid[i - 1][0];
      }
      for (int j = 1; j < m; j++) {
        if (i == 0) {
          grid[i][j] += grid[i][j - 1];
        } else {
          grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
        }
      }
    }

    for (auto& line : grid) {
      for (auto v : line) {
        if (v <= k) {
          ans++;
        }
      }
    }

    return ans;
  }
};
