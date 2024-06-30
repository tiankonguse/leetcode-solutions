// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

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
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

/*
A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

vector<ll> A;
vector<ll> RA;

const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
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
  vector<vector<ll>> dp;
  unordered_map<int, int> h;
  ll Dfs(int n, int x) {  // 前 n 个元素，有 x 个逆序数的答案个数
    if (x < 0) return 0;
    if (n == 0 && x == 0) return 1;
    if (n == 0) return 0;
    auto& ret = dp[n][x];
    if (ret != -1) return ret;

    if (h.count(n) && h[n] != x) {
      return ret = 0;  // requirements 不满足
    }

    ret = 0;
    // sum(Dfs(n-1, x - (n-i)))
    for (int i = 1; i <= n; i++) {  // 枚举最后一个位置
      // 如果为 i， 则前面 [i+1, n] 大于 i， 逆序数有 n - i 个
      ret = (ret + Dfs(n - 1, x - (n - i))) % mod;
    }
    return ret;
  }

 public:
  int numberOfPermutations(int n, vector<vector<int>>& requirements) {
    InitA(n + 1, mod);
    int m = requirements.size();
    sort(requirements.begin(), requirements.end());
    for (int i = 1; i < m; i++) {
      int endi = requirements[i][0];
      int cnti = requirements[i][1];

      if (cnti < requirements[i - 1][1]) return 0;  // 单调性不合法，不存在
      if (C(endi+1, 2, mod) < cnti) return 0;  // 参数不合法，不存在
    }
    for (auto& r : requirements) {
      h[r[0] + 1] = r[1];
    }

    int endIndex = requirements[m - 1][0] + 1;
    int endVal = requirements[m - 1][1];

    // 题意保障最后一个一定是 n, 这里不做这个假设
    int N = C(endIndex, 2, mod);
    dp.resize(endIndex + 1, vector<ll>(N + 1, -1));
    ll ans = Dfs(endIndex, endVal);
    return C(n, endIndex, mod) * ans % mod;
  }
};