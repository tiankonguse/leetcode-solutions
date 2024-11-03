
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

ll dp[10][730][88];  // 差分
class Solution {
  ll n;
  ll sum = 0;
  ll sum2 = 0;
  ll EventAll, OddAll;
  vector<ll> nums;
  vector<ll> counts;
  // -sum2 ... -1    0     1      ... sum2
  //  0       sum2-1 sum2 sum2+1  ... sum2*2
  //  -odd ... -1   0     1 ...     even
  //     0 ... -1 odd odd+1 ... odd+even
  ll Dfs(const ll V, const ll S, const ll N) {
    if (S < -sum2 || S > sum2 || N < -OddAll || N > EventAll) return 0;
    if (V == -1) {
      if (S == 0 && N == EventAll - OddAll) {
        return 1;
      }
      return 0;
    }

    ll& ret = dp[V][S + sum2][N + OddAll];
    if (ret != -1) return ret;

    const ll K = nums[V];
    if (K == 0) {
      return ret = Dfs(V - 1, S, N);
    }

    const ll P = n - counts[V];  // [V+1,9] 已选择的数字个数
    const ll selectEven = (N + P) / 2;
    const ll selectOdd = (P - N) / 2;
    const ll leftEven = EventAll - selectEven;
    const ll leftOdd = OddAll - selectOdd;

    ret = 0;
    for (ll i = 0; i <= K; i++) {
      // 偶数选择 i 个，偶数选择 K-i 个
      const ll trySelectEven = i;
      const ll trySelectOdd = K - i;
      if (trySelectEven > leftEven) continue;
      if (trySelectOdd > leftOdd) continue;
      const ll even = C(leftEven, trySelectEven, mod);
      const ll odd = C(leftOdd, trySelectOdd, mod);
      const ll evenOdd = (even * odd) % mod;
      const ll nextAns = Dfs(V - 1, S + trySelectEven * V - trySelectOdd * V,
                             N + trySelectEven - trySelectOdd);
      ret = (ret + evenOdd * nextAns) % mod;
    }
    return ret;
  }

 public:
  int countBalancedPermutations(const string& num) {
    n = num.size();
    nums.resize(10, 0);
    for (auto c : num) {
      nums[c - '0']++;
      sum += c - '0';
    }
    if (sum % 2 == 1) {
      return 0;
    }
    counts.resize(10, 0);
    counts[0] = nums[0];
    for (int i = 1; i <= 9; i++) {
      counts[i] = counts[i - 1] + nums[i];
    }

    sum2 = sum / 2;
    InitA(sum, mod);
    memset(dp, -1, sizeof(dp));
    EventAll = (n + 1) / 2;
    OddAll = n / 2;
    return Dfs(9, 0, 0);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& num, const int& ans) {
  TEST_SMP1(Solution, countBalancedPermutations, ans, num);
}

int main() {
  Test("11", 1);
  Test("123", 2);
  Test("1111111111", 1);
  Test("112", 1);
  Test("12345", 0);
  Test("08143", 12);
  Test("1234", 8);
  Test("0123", 8);
  Test("01236", 12);
  return 0;
}

#endif