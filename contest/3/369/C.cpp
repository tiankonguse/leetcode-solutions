// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minIncrementOperations(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> dp(n, INT_MAX);
    vector<ll> DP(n, INT_MAX);

    auto SolverK = [&k, &nums](ll p) -> ll {
      ll v = nums[p];
      if (v >= k) return 0;
      return k - v;
    };
    auto GetDPVal = [&DP](int p) -> ll {
      ll ans = INT_MAX;
      for(int i=1;i<=3;i++){
        if(p-i < 0) return 0;
        ans = min(ans, DP[p-i]);
      }
      return ans;
    };
    auto GetdpVal = [&dp](int p) -> ll {
      if (p < 0) return INT_MAX;
      return dp[p];
    };
    for (int i = 0; i < n; i++) {
      dp[i] = DP[i] = SolverK(i) + GetDPVal(i);
      for (int j = 1; j < 3; j++) {
        DP[i] = min(DP[i], GetdpVal(i - j));
      }
      printf("i=%d dp=%lld DP=%lld\n", i, dp[i], DP[i]);
    }
    return DP[n - 1];
  }
};
