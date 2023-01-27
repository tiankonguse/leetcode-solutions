// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  // nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
  // nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
  ll Rev(ll v) {
    ll V = 0;
    while (v) {
      V = V * 10 + v % 10;
      v /= 10;
    }
    return V;
  }
  int countNicePairs(vector<int>& nums) {
    unordered_map<ll, ll> m;
    ll ans = 0;
    for (ll v : nums) {
      ll V = v - Rev(v);
      ans = (ans + m[V]) % mod;
      m[V]++;
    }

    return ans;
  }
};