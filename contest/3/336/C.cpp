// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long beautifulSubarrays(vector<int>& nums) {
    ll ans = 0;
    map<ll, ll> m;
    m[0] = 1;

    ll pre = 0;
    for (ll v : nums) {
      pre ^= v;
      ans += m[pre];
      m[pre]++;
    }
    return ans;
  }
};