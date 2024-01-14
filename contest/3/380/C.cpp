// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll SolverBit(ll n, int x) {
    ll ans = 0;
    const ll base = 1LL << x;

    n++;

    ans += n / base * base / 2;
    const ll left = n % base;

    if (left > base / 2) {
      ans += left - base / 2;
    }

    return ans;
  }
  ll SolverStep(ll n, int x) {  //小于等于 n 数字中 1 的个数和
    ll ans = 0;
    for (int i = 1; i <= 60; i++) {
      if (i % x == 0) {
        ans += SolverBit(n, i);
      }
    }
    return ans;
  }

 public:
  ll findMaximumNumber(const ll k, const int x) {
    ll l = 0, r = 1LL << 50;  //[l, r)
    while (l < r) {
      ll mid = (l + r) / 2;
      if (SolverStep(mid, x) <= k) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return r - 1;
  }
};