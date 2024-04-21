// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumOperations(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid.front().size();

    vector<vector<int>> stat(m, vector<int>(12, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int v = grid[i][j];
        stat[j][v]++;
      }
    }

    vector<vector<int>> dp(m, vector<int>(12, INT_MAX));
    for (int v = 0; v < 12; v++) {
      dp[0][v] = n - stat[0][v];  // 共 n 个，num个相同
    }
    for (int j = 1; j < m; j++) {
      for (int v = 0; v < 12; v++) {
        // 当前位置选择为 V， 需要修改的个数
        const int num = n - stat[j][v];
        int& ret = dp[j][v];
        for (int V = 0; V < 12; V++) {
          if (V == v) continue;
          int tmp = num + dp[j - 1][V];
          ret = min(ret, tmp);
        }
      }
    }
    int ans = INT_MAX;
    for (auto v : dp[m - 1]) {
      ans = min(ans, v);
    }

    return ans;
  }
};