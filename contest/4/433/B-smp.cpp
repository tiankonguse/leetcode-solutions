
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
    // printf("C(0,0)=%lld\n", C(0, 0));
    sort(nums.begin(), nums.end());
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
      ll v = nums[i - 1];
      for (int k = 0; k < K; k++) {
        // 枚举最大值: [1, i-1]里面选择 k-1 个
        ans = (ans + v * C(i - 1, k)) % mod1e7;

        // 枚举最小值: [i+1, n] 里面选择 k-1个
        ans = (ans + v * C(n - (i + 1) + 1, k)) % mod1e7;
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