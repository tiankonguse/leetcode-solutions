
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

ll qpow(ll x, ll v, ll mod = 10) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}
ll inv(ll x, ll mod = 10) { return qpow(x, mod - 2, mod); }

/*
A(n,r)=n(n-1)…(n-r+1)
A(n,r)=n!/(n-r)!
C(n,r)=A(n,r)/r!
*/

vector<ll> A2;
vector<ll> A5;
vector<ll> A;
vector<ll> RA;

void InitA(int n, int mod = 10) {
  A.resize(n + 1);
  A2.resize(n + 1, 0);
  A5.resize(n + 1, 0);

  A[0] = 1;
  for (int i = 1; i <= n; i++) {
    ll x = i;
    int x2 = 0, x5 = 0;
    while (x % 2 == 0) {
      x2++;
      x /= 2;
    }
    while (x % 5 == 0) {
      x5++;
      x /= 5;
    }
    A[i] = (A[i - 1] * x) % mod;
    A2[i] = A2[i - 1] + x2;
    A5[i] = A5[i - 1] + x5;
  }

  RA.resize(n + 1);
  RA[n] = inv(A[n], mod);
  for (int i = n; i > 0; i--) {
    ll x = i;
    int x2 = 0, x5 = 0;
    while (x % 2 == 0) {
      x2++;
      x /= 2;
    }
    while (x % 5 == 0) {
      x5++;
      x /= 5;
    }
    RA[i - 1] = RA[i] * x % mod;
  }
}

ll C(ll n, ll k, ll mod = 10) {
  return A[n] * RA[k] * RA[n - k] * qpow(2, A2[n] - A2[k] - A2[n - k]) * qpow(5, A5[n] - A5[k] - A5[n - k]) % mod;
}
class Solution {
 public:
  bool hasSameDigits(string s) {
    int n = s.size();
    InitA(n, 10);

    vector<int> nums;
    nums.reserve(s.size());
    for (auto c : s) {
      nums.push_back(c - '0');
    }
    int ret = 0;
    for (int i = 0; i + 1 < n; i++) {
      ret += (nums[i] - nums[i + 1]) * C(n - 2, i) % 10;
    }
    ret %= 10;
    return ret == 0;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  // Test({1, 2, 3}, 3);
  // vector<vector<int>> dp;
  // int N = 40;
  // dp.resize(N, vector<int>(N, 0));
  // for (int i = 0; i < N; i++) {
  //   dp[i][0] = 1;
  //   printf("%d ", dp[i][0]);
  //   for (int j = 1; j <= i; j++) {
  //     dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % 10;
  //     printf("%d ", dp[i][j]);
  //   }
  //   printf("\n");
  // }

  return 0;
}

#endif