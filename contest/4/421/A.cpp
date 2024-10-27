// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}

class Solution {
  ll Skip(const vector<int>& nums, ll p) {
    ll n = nums.size();
    ll lcm = 0, gcd = 0;
    if (p == 0) {
      lcm = gcd = nums.back();
    } else {
      lcm = gcd = nums.front();
    }
    for (ll i = 0; i < n; i++) {
      if (i == p) continue;
      gcd = Gcd(gcd, nums[i]);
      lcm = nums[i] / Gcd(lcm, nums[i]) * lcm;
    }
    return gcd * lcm;
  }

 public:
  ll maxScore(vector<int>& nums) {
    ll n = nums.size();
    ll ans = Skip(nums, -1);
    for (ll i = 0; i < n; i++) {
      ans = max(ans, Skip(nums, i));
    }
    return ans;
  }
};