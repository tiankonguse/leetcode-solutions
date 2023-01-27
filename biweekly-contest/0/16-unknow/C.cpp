// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const ll inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int minimizeSet(ll divisor1, ll divisor2, ll uniqueCnt1, ll uniqueCnt2) {
    ll ab = divisor1 / gcd(divisor1, divisor2) * divisor2;

    ll l = 1, r = 7 * mod;  // [l,r)
    while (l < r) {
      ll mid = (l + r) / 2;

      ll only1 = mid / divisor2 - mid / ab;
      ll only2 = mid / divisor1 - mid / ab;
      ll double12 = mid - mid / divisor2 - mid / divisor1 + mid / ab;

      ll shouldDouble = 0;
      shouldDouble += max(0ll, uniqueCnt1 - only1);
      shouldDouble += max(0ll, uniqueCnt2 - only2);

      if (shouldDouble <= double12) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};
