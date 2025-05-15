
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
ll dp[52][32][32][32];
const int mod = 1e9 + 7;
class Solution {
 public:
  int magicalSum(int M, int K, vector<int>& nums) {
    InitA(52, mod);
    // sort(nums.begin(), nums.end());
    int n = nums.size();
    memset(dp, -1, sizeof(dp));
    auto NextKMask = [&](int p, int mask, int k) -> pair<int, int> {
      if (p == n) {
        int one = __builtin_popcount(mask);
        return {0, k - one};
      }
      if (mask & 1) {
        k--;
      }
      mask >>= 1;
      return {mask, k};
    };
    auto Dfs = [&](auto& Dfs, const int p, const int m, pair<int, int> kmask) -> ll {
      const auto [mask, k] = kmask;
      if (m < 0 || k < 0) return 0;
      ll& ret = dp[p][m][mask][k];
      if (ret != -1) return ret;
      if (p == n) {
        if (m != 0 || k != 0) { 
          return ret = 0;
        }
        return ret = 1;
      }

      ret = 0;
      ll base = 1;
      for (int i = 0; i <= m; i++) {  // 选择 i 个
        ll tmp = C(m, i, mod) * base % mod;
        ret = (ret + tmp * Dfs(Dfs, p + 1, m - i, NextKMask(p + 1, mask + i, k))) % mod;
        base = base * nums[p] % mod;
      }

      return ret;
    };
    return Dfs(Dfs, 0, M, {0, K});
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif