#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll gcd(ll a, ll b) {
    if (b == 0)
      return a;
    else
      return gcd(b, a % b);
  }
  ll findIndex(ll A, ll B, ll loopIndex) {
    ll aNum = 0, bNum = 0;
    while (1) {
      if (loopIndex == 0) {
        return min(aNum, bNum);
      }
      if (aNum < bNum) {
        aNum += A;
      } else if (aNum > bNum) {
        bNum += B;
      } else {
        aNum += A;
        bNum += B;
      }
      loopIndex--;
    }
  }

 public:
  int nthMagicalNumber(int N, int A, int B) {
    ll mod = 1000000007;
    ll minGcd = gcd(A, B);
    ll maxGcd = A / minGcd * B;
    ll loop = maxGcd / A + maxGcd / B - 1;

    ll loopNum = N / loop;
    ll loopIndex = N % loop;

    ll indexVal = findIndex(A, B, loopIndex);

    ll ans = (loopNum * maxGcd) % mod;
    ans = (ans + indexVal) % mod;
    return ans;
  }
};
