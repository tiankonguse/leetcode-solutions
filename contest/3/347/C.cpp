// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll minimumCost(string s) {
    vector<ll> nums;
    nums.reserve(s.length());

    nums.push_back(0);
    char pre = s.front();
    for (auto c : s) {
      if (c != pre) {
        nums.push_back(0);
      }
      pre = c;
      nums.back()++;
    }
    ll n = nums.size();
    vector<ll> sum(n + 2, 0);
    vector<ll> leftSum(n + 2, 0);
    vector<ll> rightSum(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + nums[i - 1];
    }

    for (int i = 1; i <= n; i++) {
      leftSum[i] = sum[i] + leftSum[i - 1];
    }
    for (int i = n; i >= 1; i--) {
      rightSum[i] = (sum[n] - sum[i - 1]) + rightSum[i + 1];
    }

    auto F = [](ll n) -> ll {
      if (n < 1) return 0;
      return (1 + n) * n / 2;
    };
    auto Cal = [&leftSum, &rightSum](int i, int n) -> ll {
      ll ans1 = leftSum[i - 1] + rightSum[i + 1];  // 答案与 i 相同
      ll ans2 = leftSum[i] + rightSum[i + 2];      // 答案与 i 相反
      return min(ans1, ans2);
    };
    ll ans = min(rightSum[1], rightSum[2]);
    for (int i = 1; i < n; i++) {
      // [1, i] [i+1, n]
      ans = min(ans, Cal(i, n));
    }
    return ans;
  }
};