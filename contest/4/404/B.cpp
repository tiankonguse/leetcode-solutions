// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int maximumLength(vector<int>& nums) {
    int ans = 0;
    int dp[2] = {0, 0};
    int dp2[2] = {0, 0};
    for (auto v : nums) {
      v = v % 2;
      dp[v] = dp[1 - v] + 1;
      dp2[v]++;
      ans = max(dp[v], ans);
      ans = max(dp2[v], ans);
    }
    return ans;
  }
};