// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int miceAndCheese(vector<int>& nums1, vector<int>& nums2, int K) {
    int N = nums1.size();
    vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));

    for (int n = 1; n <= N; n++) {  // 不吃
      dp[n][0] = dp[n - 1][0] + nums2[n - 1];
    }
    for (int k = 1; k <= K; k++) {
      dp[k][k] = dp[k - 1][k - 1] + nums1[k - 1];  // 全吃
      for (int n = k + 1; n <= N; n++) {
        dp[n][k] =
            max(dp[n - 1][k - 1] + nums1[n - 1], dp[n - 1][k] + nums2[n - 1]);
      }
    }
    return dp[N][K];
  }
};