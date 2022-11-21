#include <bits/stdc++.h>

#include "base.h"
using namespace std;

const int N = 1000;
class Solution {
  vector<vector<double>> dp;

  double Cal(int i, int j) {
    i = max(i, 0);
    j = max(j, 0);
    return dp[i][j];
  }

 public:
  double soupServings(int n) {
    n = (n + 24) / 25;

    n = min(n, N);

    dp.resize(n + 1, vector<double>(n + 1, 0.0));

    for (int i = 1; i <= n; i++) {
      dp[0][i] = 1.0;
      dp[i][0] = 0.0;
    }
    dp[0][0] = 0.5;

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 0; k < 4; k++) {
          dp[i][j] += Cal(i - (4 - k), j - k) / 4;
        }
      }
    }

    return dp[n][n];
  }
};
