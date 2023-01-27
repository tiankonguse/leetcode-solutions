// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
 public:
  int countOrders(int n) {
    ll ans = 1;
    ll a = 0;
    for (int i = 1; i <= n; i++) {
      // a+1, a, a-1, ...,1
      ans = (ans * (a + 1) * (a + 2) / 2) % mod;
      a += 2;
    }

    return ans;
  }
};
