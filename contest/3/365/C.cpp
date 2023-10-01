// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minSizeSubarray(vector<int>& nums, ll target) {
    int n = nums.size();
    ll sum = 0;
    for (auto v : nums) {
      sum += v;
    }

    ll ansBase = target / sum;
    target %= sum;

    ll ans = 0;

    if (target > 0) {
      ans = 2 * n;
      unordered_map<ll, ll> h;
      ll sum = 0;
      h[sum] = -1;
      for (int i = 0; i < n * 2; i++) {
        sum += nums[i % n];
        ll dis = sum - target;
        if (h.count(dis)) {
          ans = min(ans, i - h[dis]);
        }
        h[sum] = i;
      }
      if (ans == 2 * n) return -1;
    }
    return ans + ansBase * n;
  }
};
