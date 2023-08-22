// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  int maximizeTheProfit(int n, vector<vector<int>>& offers) {
    vector<int> dp(n + 1, 0);
    sort(offers.begin(), offers.end(),
         [](auto& a, auto& b) { return a[0] < b[0]; });
    int offset = 0;  //[0, offset]
    for (auto& v : offers) {
      int l = v[0] + 1, r = v[1] + 1, c = v[2];
      while (offset < l - 1) {
        dp[offset + 1] = max(dp[offset], dp[offset + 1]);
        offset++;
      }
      dp[r] = max(dp[r], dp[l - 1] + c);
    }
    while (offset < n) {
      dp[offset + 1] = max(dp[offset], dp[offset + 1]);
      offset++;
    }
    return dp[n];
  }
};