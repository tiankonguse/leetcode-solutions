#include <bits/stdc++.h>
typedef long long ll;

// 快速幂
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

// 模逆元，mod 必须为质数
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

/*
计算排列组合

A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

vector<ll> A;
vector<ll> RA;

void InitA(int n, int mod) {
  A.resize(n + 1);
  A[0] = 1;

  for (int i = 1; i <= n; i++) {
    A[i] = (A[i - 1] * i) % mod;
  }

  RA.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    RA[i] = inv(A[i], mod);
  }
}

ll C(ll n, ll r, ll mod) {
  ll Anr = A[n] * RA[n - r] % mod;
  return Anr * RA[r] % mod;
}

ll P(ll n, ll r, ll mod) { return A[n] * RA[n - r] % mod; }