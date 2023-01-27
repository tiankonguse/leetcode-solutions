// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  // 算法是计算子序列
  int minCost(vector<int>& nums, ll k) {
    unordered_map<int, int> m;
    for (auto v : nums) {
      m[v]++;
    }
    vector<ll> counts;
    int maxV = 0;
    for (auto [k, v] : m) {
      counts.push_back(v);
      maxV = max(maxV, v);
    }
    sort(counts.begin(), counts.end());

    int n = counts.size();
    vector<ll> sums(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      sums[i] = sums[i - 1] + counts[i - 1];
    }

    ll ans = INT_MAX;
    int l = 0, r = n;                 // [l, r)
    for (ll i = 1; i <= maxV; i++) {  // 分 i 组
      auto it = upper_bound(counts.begin(), counts.end(), i);
      int j = it - counts.begin();
      ll tmp = k * i + sums[n] - sums[j] - (n - j) * (i - 1);
      ans = min(ans, k * i);
    }

    return ans;
  }
};
