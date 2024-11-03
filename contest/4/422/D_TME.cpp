
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

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

ll dp[10][361][361][42][42];
class Solution {
  ll sum = 0;
  ll sum2 = 0;
  vector<ll> nums;

  ll Dfs(const ll V, const ll S0, const ll S1, const ll N0, const ll N1) {
    if (S0 < 0 || S1 < 0) return 0;
    if (V == -1) {
      if (S0 == 0 && S1 == 0) {
        return 1;
      }
      return 0;
    }

    ll& ret = dp[V][S0][S1][N0][N1];
    if (ret != -1) return ret;

    const ll K = nums[V];
    if (K == 0) {
      return ret = Dfs(V - 1, S0, S1, N0, N1);
    }

    ret = 0;
    for (ll i = 0; i <= K; i++) {
      // 偶数选择 i 个，奇数选择 K-i 个
      const ll n0 = i;
      const ll n1 = K - n0;
      if (S0 < n0 * V || S1 < n1 * V) continue;
      if (N0 < n0 || N1 < n1) continue;
      const ll C0 = C(N0, n0, mod);
      const ll C1 = C(N1, n1, mod);
      const ll C01 = (C0 * C1) % mod;
      const ll tmp = Dfs(V - 1, S0 - n0 * V, S1 - n1 * V, N0 - n0, N1 - n1);
      ret = (ret + C01 * tmp) % mod;
      printf(
          "V=%lld K=%lld S0=%lld S1=%lld  C0(%lld,%lld)=%lld "
          "C1(%lld,%lld)=%lld tmp=%lld "
          "ad=%lld\n",
          V, K, S0, S1, N0, n0, C0, N1, n1, C1, tmp, (C01 * tmp) % mod);
    }
    if (ret || 1) {
      MyPrintf("V=%lld K=%lld S0=%lld S1=%lld N0=%lld N1=%lld ret=%lld\n", V, K,
               S0, S1, N0, N1, ret);
    }
    return ret;
  }

 public:
  int countBalancedPermutations(const string& num) {
    int n = num.size();
    nums.resize(10, 0);
    for (auto c : num) {
      nums[c - '0']++;
      sum += c - '0';
    }
    if (sum % 2 == 1) {
      return 0;
    }
    sum2 = sum / 2;
    InitA(sum, mod);
    memset(dp, -1, sizeof(dp));
    return Dfs(9, sum2, sum2, (n + 1) / 2, n / 2);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& num, const int& ans) {
  TEST_SMP1(Solution, countBalancedPermutations, ans, num);
}

int main() {
  Test("123", 2);
  // Test("11", 1);
  // Test("112", 1);
  // Test("12345", 0);
  // Test("08143", 12);
  // Test("1234", 8);
  // Test("0123", 8);
  // Test("01236", 12);
  return 0;
}

#endif