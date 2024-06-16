// #include <bits/stdc++.h>

#include "base.h"
using namespace std;


typedef long long ll;
class Solution {
 public:
  ll countCompleteDayPairs(vector<int>& hours) {
    vector<ll> dp(25, 0);
    for (ll v : hours) {
      dp[v % 24]++;
    }
    ll ans = 0;
    ans += (dp[0] * (dp[0] - 1)) / 2;
    for (int i = 1; i < 12; i++) {
      ans += dp[i] * dp[24 - i];
    }
    ans += (dp[12] * (dp[12] - 1)) / 2;
    return ans;
  }
};
