// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int numberOfSubmatrices(vector<vector<char>>& grid) {
    int ans = 0;
    int n = grid.size();
    int m = grid.front().size();

    vector<vector<int>> dp[2];
    dp[0].resize(n + 1, vector<int>(m + 1, 0));
    dp[1].resize(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 0; k < 2; k++) {
          dp[k][i][j] = dp[k][i][j - 1] + dp[k][i - 1][j] - dp[k][i - 1][j - 1];
        }
        if (grid[i - 1][j - 1] == 'X') {
          dp[0][i][j]++;
        } else if (grid[i - 1][j - 1] == 'Y') {
          dp[1][i][j]++;
        }
        if (dp[0][i][j] == dp[1][i][j] && dp[0][i][j]) {
          ans++;
        }
      }
    }
    return ans;
  }
};