// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll countGood(vector<int>& nums, int k) {
    unordered_map<ll, ll> m;
    ll ans = 0;

    int l = 0, r = 0;  // [l,r)
    int n = nums.size();
    int K = 0;
    while (l < n) {
      while (r < n && K < k) {  // add r
        K += m[nums[r]];
        m[nums[r]]++;
        r++;
      }

      if (K >= k) {
        ans += n - r + 1;
      }

      m[nums[l]]--;
      K -= m[nums[l]];
      l++;
    }
    return ans;
  }
};
