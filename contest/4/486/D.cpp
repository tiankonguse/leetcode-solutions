
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

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

ll CC[55][55];
void InitCC(int n) {
  CC[0][0] = 1;
  for (int i = 1; i < n; ++i) {
    CC[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      CC[i][j] = CC[i - 1][j - 1] + CC[i - 1][j];
    }
  }
}

class Solution {
 public:
  vector<int> bits;
  ll Dfs(const int b, const ll n, const int k) {
    if (k == 0) {
      assert(n == 0);
      return 0;
    }
    if (n == 0) {
      return (1LL << k) - 1;
    }
    // 不选择
    int B = b + 1;
    ll num = CC[b][k];
    if (num >= n + 1) {
      return Dfs(b - 1, n, k);
    } else {
      return Dfs(b - 1, n - num, k - 1) | (1LL << b);
    }
  }
  ll nthSmallest(long long n, int k) {  //
    InitCC(51);
    n--;  // 从 0 开始
    return Dfs(50, n, k);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const long long n, const int k, const ll ans) {  //
  TEST_SMP2(Solution, nthSmallest, ans, n, k);
}

int main() {
  {
    Test(4, 2, 9);
    Test(3, 1, 4);
  }
  return 0;
}

#endif