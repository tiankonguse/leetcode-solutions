#include "base.h"

typedef long long ll;
class Solution {
 public:
  int consecutiveNumbersSum(int n) {
    int ans = 0;
    // a, a+1, a+2, a+(k-1)
    // (a + a+k-1) * k /2 = n
    // k * (k+1) = 2n
    // a = (2n/k - k + 1)/2
    ll n2 = n * 2;
    for (ll k = 1; k * (k + 1) <= n2; k++) {
      if (n2 % k) continue;
      ll b = n2 / k - k + 1;
      if (b < 0) continue;
      if (b % 2) continue;
      ans++;
    }

    return ans;
  }
};