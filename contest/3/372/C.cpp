// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  /*
  // 首次遇到
  // 1) (a + 2^i + 2^j) * (a) = a^2 + a * 2^i + a * 2^j
  // 2) (a + 2^i) * (a + 2^j) = a^2 + a*2^j + a*2^i + 2^i * w^j

  // 第三次遇到不同 i>j
  // (a + 2^i + 2^k) * (a + 2^j) = a^2 + a*2^j + a*2^i + a*2^k + 2^i*2^j +
  2^k*2^j
  // (a + 2^i ) * (a + 2^j+ 2^k) = a^2 + a*2^j + a*2^i + a*2^k + 2^i*2^j +
  2^k*2^i
  */
 public:
  int maximumXorProduct(long long a, long long b, int n) {
    bool first = true;
    if ((a >> n) != (b >> n)) {
      first = false;
      if (a < b) {
        swap(a, b);
      }
    }
    ll one = 1;
    for (int i = n - 1; i >= 0; i--) {
      ll bit = one << i;
      ll av = (a >> i) & 1;
      ll bv = (b >> i) & 1;

      a = a & ~bit;
      b = b & ~bit;

      if (av ^ bv) {
        if (first) {
          a = a | bit;
          first = false;
        } else {
          b = b | bit;
        }
      } else {
        a = a | bit;
        b = b | bit;
      }
    }
    return ((a % mod) * (b % mod)) % mod;
  }
};