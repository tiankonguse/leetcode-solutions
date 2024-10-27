// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;
// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;
  for (ll t; t = x % y; x = y, y = t);
  return y;
}
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
ll Inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

class Solution {
  vector<int> nums;
  vector<vector<vector<ll>>> dp;
  ll Dfs(const int p, ll v1, ll v2) {
    if (p < 0) {
      if (v1 == 0 || v2 == 0) return 0;  // 非空
      return v1 == v2;
    }
    ll& ret = dp[p][v1][v2];
    if (ret != -1) return ret;
    const ll v = nums[p];

    ret = Dfs(p - 1, v1, v2);  // 不选择
    ret = (ret + Dfs(p - 1, Gcd(v1, v), v2)) % mod;
    ret = (ret + Dfs(p - 1, v1, Gcd(v2, v))) % mod;
    return ret;
  }

 public:
  int subsequencePairCount(vector<int>& nums_) {
    nums.swap(nums_);
    int n = nums.size();
    dp.resize(n + 1, vector<vector<ll>>(201, vector<ll>(201, -1)));
    ll num = Dfs(n - 1, 0, 0);
    return num;
    // return num * Inv(2, mod) % mod;
  }
};