// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minTaps(int n, vector<int>& ranges) {
    n++;
    vector<int> dp(n + 1, INT_MAX);
    for (int i = 0; i < n; i++) {
      int v = ranges[i];
      if (v == 0) continue;

      int l = max(0, i - v);
      int r = min(i + v, n);

      if (l != 0 && dp[l] == INT_MAX) continue;
      for (int j = l; j <= r; j++) {
        if (l == 0) {
          dp[j] = 1;
        } else {
          dp[j] = min(dp[j], dp[l] + 1);
        }
      }
    }
    if (dp[n - 1] == INT_MAX) return -1;
    return dp[n - 1];
  }
};