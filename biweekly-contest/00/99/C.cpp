// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
typedef long long ll;
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
class Solution {
 public:
  int countWays(vector<vector<int>>& ranges) {
    sort(ranges.begin(), ranges.end(), [](auto& a, auto& b) {
      if (a[0] == b[0]) {
        return a[1] > b[1];
      } else {
        return a[0] < b[0];
      }
    });
    int n = 0;
    int A = -1, B = -1;
    for (auto& v : ranges) {
      int a = v[0], b = v[1];
      if (a <= B) {
        B = max(B, b);
      } else {
        n++;
        A = a;
        B = b;
      }
    }
    return qpow(2, n, mod);
  }
};
