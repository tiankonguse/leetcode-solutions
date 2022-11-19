#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll mod = 1000000007;
class Solution {
 public:
  int sumSubseqWidths(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    ll ans = 0;
    ll preNum = 0;
    ll preSum = 0;
    ll last = nums.front();
    for (ll v : nums) {
      ll dis = v - last;
      last = v;
      ans = (ans + preSum + dis * preNum) % mod;
      preSum = (preSum + dis * preNum) * 2 % mod;
      preNum = (preNum * 2 + 1) % mod;
    }
    return ans;
  }
};