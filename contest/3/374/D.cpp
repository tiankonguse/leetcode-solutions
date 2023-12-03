// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;

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
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

/*
A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

const int N = 100010;
ll A[N];
ll RA[N];
ll pow2[N];
int max_n = 1;

void InitA(int n, ll mod) {
  A[0] = 1;
  RA[0] = 1;
  pow2[0] = 1;

  while (max_n <= n) {
    A[max_n] = (A[max_n - 1] * max_n) % mod;
    RA[max_n] = inv(A[max_n], mod);
    pow2[max_n] = (pow2[max_n - 1] * 2) % mod;
    max_n++;
  }
}

ll C(ll n, ll r, ll mod) {
  ll Anr = A[n] * RA[n - r] % mod;
  return Anr * RA[r] % mod;
}

class Solution {
 public:
  int numberOfSequence(int n, vector<int>& sick) {
    InitA(n, mod);
    int pre = -1;
    ll sum = n - sick.size();
    ll ans = 1;
    for (auto c : sick) {
      if (pre + 1 != c) {
        ll num = c - pre - 1;
        ans = (ans * C(sum, num, mod)) % mod;
        if (pre != -1) {
          ans = (ans * pow2[num - 1]) % mod;
        }
        sum -= num;
      }
      pre = c;
    }
    return ans;
  }
};