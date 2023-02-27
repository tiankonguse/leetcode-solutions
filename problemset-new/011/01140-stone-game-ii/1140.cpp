// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> dp;  // dp[S,M+1)
  vector<int> sums;
  int n;

  int Dfs(int s, int m) {
    if (s > n) return 0;
    int m2 = 2 * m;
    if (m2 >= n - s + 1) return sums[n] - sums[s - 1];

    int& ans = dp[s][m];
    if (ans != -1) return ans;

    ans = 0;
    int leftSum = sums[n] - sums[s - 1];
    for (int x = 1; x <= m2; x++) {
      ans = max(ans, leftSum - Dfs(s + x, max(m, x)));
    }
    return ans;
  }

 public:
  int stoneGameII(vector<int>& piles) {
    n = piles.size();

    sums.reserve(n + 1);
    sums.push_back(0);
    for (auto v : piles) {
      sums.push_back(v + sums.back());
    }

    dp.resize(n + 1, vector<int>(n + 2, -1));
    return Dfs(1, 1);
  }
};