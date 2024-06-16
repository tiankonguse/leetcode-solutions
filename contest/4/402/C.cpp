// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll maximumTotalDamage(vector<int>& power) {
    int n = power.size();

    map<ll, ll> h;
    for (ll v : power) {
      h[v]++;
    }

    map<ll, ll> H;
    ll ans = 0;
    H[-3] = 0;
    for (auto [v, num] : h) {
      auto it = H.lower_bound(v - 2);
      it--;
      H[v] = max(ans, it->second + v * num);
      ans = max(ans, H[v]);
    }

    return ans;
  }
};