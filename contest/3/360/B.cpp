// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll minimumPossibleSum(ll n, ll k) {
    ll l = k / 2;
    if (l >= n) {
      return (1 + n) * n / 2;
    }

    ll ans = 0;
    ans += (1 + l) * l / 2;
    // printf("add (%d,%d)\n", 1, l);

    ll r = k + (n - l) - 1;
    l = k;
    // printf("add (%d,%d)\n", l, r);
    ans += (l + r) * (r - l + 1) / 2;
    return ans;
  }
};