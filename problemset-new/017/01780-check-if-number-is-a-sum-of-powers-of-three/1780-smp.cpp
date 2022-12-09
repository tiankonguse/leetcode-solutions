// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  bool checkPowersOfThree(ll n) {
    ll base = 1;
    while (base <= n) {
      base = base * 3;
    }

    while (base) {
      if (n >= base) {
        n -= base;
      }
      base = base / 3;
    }

    return n == 0;
  }
};
