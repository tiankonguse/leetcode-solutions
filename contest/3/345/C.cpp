// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maxMoves(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid.front().size();
    vector<vector<int>> dp(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++) {
      dp[i][0] = 0;
    }
    int ans = 0;
    for (int j = 1; j < m; j++) {
      for (int i = 0; i < n; i++) {
        for (int k = -1; k <= 1; k++) {
          int x = i + k;
          int y = j - 1;
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          if (dp[x][y] != -1 && grid[x][y] < grid[i][j]) {
            dp[i][j] = max(dp[i][j], dp[x][y] + 1);
            ans = max(ans, dp[i][j]);
          }
        }
      }
    }
    return ans;
  }
};