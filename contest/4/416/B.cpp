// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  ll CalMaxTime(ll x, ll t) { return t * (1 + x) * x / 2; }
  ll CalMaxHeight(ll T, ll t) { return (sqrt(1.0 + 8.0 * T / t) - 1) / 2; }

 public:
  long long minNumberOfSeconds(ll mountainHeight, vector<int>& workerTimes) {
    ll l = 1;
    ll r = CalMaxTime(mountainHeight, workerTimes.front());
    while (l < r) {
      ll mid = (l + r) / 2;
      ll sum = 0;
      for (auto t : workerTimes) {
        sum += CalMaxHeight(mid, t);
      }
      if (sum >= mountainHeight) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return r;
  }
};