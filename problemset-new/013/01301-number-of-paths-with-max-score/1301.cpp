
// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  vector<int> pathsWithMaxScore(vector<string>& board) {
    int n = board.size();
    vector<vector<pair<int, int>>> dp(n + 1,
                                      vector<pair<int, int>>(n + 1, {0, 0}));

    board[0][0] = '0';
    board[n - 1][n - 1] = '0';
    dp[n][n] = {1, 1};

    vector<pair<int, int>> dirs{{1, 1}, {1, 0}, {0, 1}};
    for (int i = n - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        if (board[i][j] == 'X') continue;
        int v = board[i][j] - '0';
        auto& [sum, t] = dp[i][j];

        for (auto [x, y] : dirs) {
          auto [sum0, t0] = dp[x + i][y + j];
          if (sum0 == 0) continue;
          sum0 += v;

          if (sum0 > sum) {
            sum = sum0;
            t = t0;
          } else if (sum0 == sum) {
            t = (t + t0) % mod;
          }
        }
      }
    }
    return {max(dp[0][0].first - 1, 0), dp[0][0].second};
  }
};