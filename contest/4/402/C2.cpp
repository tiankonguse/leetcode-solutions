// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll maximumTotalDamage(vector<int>& power) {
    int n = power.size();

    map<ll, ll> h;
    for (ll v : power) {
      h[v]++;
    }
    vector<pair<ll, ll>> nums;
    nums.reserve(h.size());
    for (auto [v, num] : h) {
      nums.push_back({v, num});
    }

    vector<pair<ll, ll>> dp;
    dp.reserve(n + 2);
    dp.push_back({-3, 0});
    ll ans = 0;
    for (int i = 0; i < nums.size(); i++) {
      auto [v, num] = nums[i];
      int pos = i;
      while (dp[pos].first + 2 >= v) {
        pos--;
      }
      dp.push_back({v, max(ans, dp[pos].second + v * num)});
      ans = max(ans, dp.back().second);
    }
    return ans;
  }
};