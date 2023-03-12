// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int waysToReachTarget(int target, vector<vector<int>>& types) {
    int n = types.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(target + 1, 0));

    dp[0][0] = 1;
    for (int i = 1; i <= target; i++) dp[0][i] = 0;
    for (int i = 1; i <= n; i++) {
      int C = types[i - 1][0];
      int M = types[i - 1][1];
      for (int j = 0; j <= target; j++) {
        for (int k = 0; k <= C && k * M <= j; k++) {
          dp[i][j] = (dp[i][j] + dp[i - 1][j - k * M]) % mod;
        }
      }
    }
    return dp[n][target];
  }
};
