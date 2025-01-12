
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
ll dp[510][510][3];
class Solution {
  int n, m;

 public:
  int maximumAmount(vector<vector<int>>& coins) {
    n = coins.size();
    m = coins[0].size();
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        for (int k = 0; k < 3; k++) {
          dp[i][j][k] = INT_MIN;  // 初始化
        }
      }
    }
    for (int k = 0; k < 3; k++) {
      dp[0][1][k] = dp[1][0][k] = 0;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int v = coins[i - 1][j - 1];
        for (int k = 0; k < 3; k++) {
          dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + v);
          dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k] + v);
          if (k > 0) {
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1]);
            dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1]);
          }
          // printf("[%d,%d,%d]=%lld\n", i, j, k, dp[i][j][k]);
        }
      }
    }
    ll ans = dp[n][m][0];
    for (int k = 0; k < 3; k++) {
      ans = max(ans, dp[n][m][k]);
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif