// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;

vector<ll> A;
vector<ll> RA;
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

class Solution {
  vector<int> nums;
  int len;

  ll ans;
  void Solver() {
    for (auto& v : nums) {
      if (v == 0) continue;
      ans = ans * C(len, v, mod) % mod;
      len -= v;
      v = 0;
    }
  }

 public:
  int countAnagrams(string s) {
    ans = 1;
    len = 0;

    InitA(s.length(), mod);

    nums.resize(26, 0);
    for (auto c : s) {
      if (c == ' ') {
        Solver();
        len = 0;
      } else {
        nums[c - 'a']++;
        len++;
      }
    }
    Solver();

    return ans;
  }
};
