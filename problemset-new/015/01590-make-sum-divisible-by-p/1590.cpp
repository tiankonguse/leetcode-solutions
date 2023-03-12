// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minSubarray(vector<int>& nums, int p) {
    int n = nums.size();
    int ans = n;

    for (auto& v : nums) {
      v = v % p;
    }

    unordered_map<ll, int> h;
    vector<int> pre(n, 0);
    ll sum = 0;
    h[0] = 0;  // 前缀为空
    for (int i = 1; i <= n; i++) {
      sum = (sum + nums[i - 1]) % p;
      pre[i] = h[sum];
      h[sum] = i;
      if (sum == 0) {
        ans = min(ans, n - i);
      }
    }

    ll next = 0;
    for (int i = n; i >= 1; i--) {
      // 后缀选择 [i, n]
      next = (next + nums[i - 1]) % p;
      // 删除 [1, i]
      h[sum] = pre[h[sum]];
      sum = (sum - nums[i - 1] + p) % p;

      // 前缀寻找 pre
      ll pre = (p - next) % p;
      if (h[pre] != 0 || pre == 0) {
        ans = min(ans, i - h[pre] - 1);
      }
    }
    if (ans == n) {
      ans = -1;
    }
    return ans;
  }
};
