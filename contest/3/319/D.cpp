#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
 public:
  int maxPalindromes(string s, int k) {
    int n = s.length();

    vector<vector<int>> nums(n + 1);

    for (int i = 0; i < n; i++) {
      // 枚举中心为 i
      for (int l = i, r = i; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
        if (r - l + 1 >= k) {
          nums[r + 1].push_back(l);
        }
      }

      // 枚举中心为 i, i+1
      for (int l = i, r = i + 1; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
        if (r - l + 1 >= k) {
          nums[r + 1].push_back(l);
        }
      }
    }

    vector<int> dp(n + 1, 0);

    for (int r = 1; r <= n; r++) {
      // printf("r=%d , l = ", r);
        dp[r] = dp[r-1];
      for (auto l : nums[r]) {
        // printf("%d, ", l);

        dp[r] = max(dp[r], dp[l] + 1);
      }
      // printf("\n");
    }
    return dp[n];
  }
};
