
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
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod1e7 = 1000000007;

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

void InitA(int n, int mod = mod1e7) {
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

ll C(ll n, ll r, ll mod = mod1e7) {
  if (n < r) return 0;
  ll Anr = A[n] * RA[n - r] % mod;
  return Anr * RA[r] % mod;
}
class Solution {
 public:
  ll minMaxSums(vector<int>& nums, const int K) {
    int n = nums.size();
    InitA(n + 1);
    printf("C(0,0)=%lld\n", C(0, 0));
    sort(nums.begin(), nums.end());
    ll ans = 0;

    for (auto v : nums) {  // k = 1
      ans = (ans + v * 2) % mod1e7;
    }
    auto Sums = [](int l, int r, vector<ll>& sums) {
      if (l == 0) return sums[r];
      return (sums[r] - sums[l - 1] + mod1e7) % mod1e7;
    };
    for (int k = 2; k <= K; k++) {
      vector<ll> sums(n + 1, 0);
      if (k == 2) {
        sums[0] = 1;
      }
      for (int i = max(1, k - 2); i <= n; i++) {
        sums[i] = (sums[i - 1] + C(i, k - 2)) % mod1e7;
      }
      for (int l = 1; l <= n; l++) {
        const int r = l + k - 1;
        if (r <= n) {
          const int L = r - l - 1;  // k-2
          const int R = n - l - 1;
          ans = (ans + nums[l - 1] * Sums(L, R, sums)) % mod1e7;
          printf("l=%d L=%d R=%d v=%d Sums=%lld\n", l, L, R, nums[l - 1], Sums(L, R, sums));
        }
      }
      for (int i = 1; i <= n; i++) {
        // [i-n-1, i-2]
        if (i - 2 >= k - 2) {
          const int L = 0;
          const int R = i - 2;
          ans = (ans + nums[i - 1] * Sums(L, R, sums)) % mod1e7;
          printf("i=%d L=%d R=%d v=%d Sums=%lld\n", i, L, R, nums[i - 1], Sums(L, R, sums));
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif