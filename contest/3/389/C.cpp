// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  int minimumDeletions(const string& word, int k) {
    unordered_map<char, int> h;
    for (auto c : word) {
      h[c]++;
    }
    vector<ll> nums;
    nums.reserve(26);
    for (auto [k, v] : h) {
      nums.push_back(v);
    }
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<ll> sums(n + 1, 0);  // 前缀和
    for (int i = 1; i <= n; i++) {
      sums[i] = sums[i - 1] + nums[i - 1];
       // printf("i=%d %lld sum=%lld\n", i, nums[i-1], sums[i]);
    }

    ll ans = word.size();
    for (auto v : nums) {  // 枚举下边界
      ll l = v;
      ll r = l + k;

      auto left = lower_bound(nums.begin(), nums.end(), l);
      auto right = upper_bound(nums.begin(), nums.end(), r);

      ll tmp = 0;
      if (left != nums.begin()) {  // 前面的都不够，都需要删除
        int pos = left - nums.begin();
        tmp += sums[pos];
      }

      if (right != nums.end()) {  // 后面的多了，需要删除对齐 r
        int pos = right - nums.begin();
        tmp += sums[n] - sums[pos] - (n - pos) * r;
      }
      // printf("v=%lld l=%lld r=%lld [%d, %d] tmp=%lld\n", v, l, r, left - nums.begin(), right - nums.begin(), tmp);

      ans = min(ans, tmp);
    }
    return ans;
  }
};