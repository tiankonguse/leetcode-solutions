
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
/*
定义: F(n,k) n 拆分为 k 个数字序列的方案数，等于 n-1 个空隙中插入 k-1 个隔板的方案数，即 C(n-1, k-1)
定义：G(n,k) n 拆分为 k 个数字序列的方案数，要求至少有一个数字是偶数
定义：H(n,k) n 拆分为 k 个数字序列的方案数，要求数字全是奇数

G(n,k) =  F(n,k) - H(n,k)

H(n,k)，n个球按顺序分k组，每组都为奇数的方案数。

H(n, k) = P(n-k, k)，每个预先分配一个，则等价与n个球按顺序分k组，每组都为偶数(可以为空)的方案数。

P(n, k) 划分 K 组，都为 偶数，两两结合，则等价与 n/2 个求按顺序分 k 组，可以为空的方案数。
Q(n, k) n 个球按顺序分 k 组，可以为空的方案数，等价于 C(n+k, k)。


n 为奇数，k 为偶数，则都是答案， C(n-1, k-1)
n 为奇数，k 为奇数，至少一个后, n-k 为偶数, k 为奇数。
n 为偶数，k 为偶数，按公式来
n 为偶数，k 为奇数。

G(n,k) =  F(n,k) - H(n,k)
H(n,k) = P(n-k, k)

*/

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
  if (n < r) return 0;
  ll Anr = A[n] * RA[n - r] % mod;
  return Anr * RA[r] % mod;
}

const ll mod = 1000000007;

// n 个球按顺序分 k 组，不能空的方案数
ll F(ll n, ll k) { return C(n - 1, k - 1, mod); }

// n 个球按顺序分 k 组，可以为空的方案数，等价于 C(n+k-1, k-1)。
ll Q(ll n, ll k) { return C(n + k - 1, k - 1, mod); }

// n个球按顺序分k组，每组都为偶数(可以为空)的方案数。
ll P(ll n, ll k) {
  if (n & 1) return 0;
  return Q(n / 2, k);
}
// H(n,k)，n个球按顺序分k组，每组都为奇数的方案数。
ll H(ll n, ll k) { return P(n - k, k); }

// G(n,k)，n个球按顺序分k组，至少有一个偶数的方案数。
ll G(ll n, ll k) { return (F(n, k) - H(n, k) + mod) % mod; }

class Solution {
 public:
  int countValidSequences(int n, int k) {  //
    InitA(2 * n, mod);
    return G(n, k);
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