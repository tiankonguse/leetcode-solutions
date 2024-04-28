// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  long long minEnd(ll n, const ll x) {
    n--;

    ll ans = 0;
    int nOffset = 0;
    int ansOffset = 0;
    while (n) {
      while ((x >> ansOffset) & 1) {
        ans |= 1LL << ansOffset;
        ansOffset++;
      }
      if (n & 1) {
        ans |= 1LL << ansOffset;
      }
      n = n / 2;
      ansOffset++;
    }
    ans |= x;
    return ans;
  }
};
