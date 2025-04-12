// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int MOD = 1e9 + 7;
ll fac[N], inv[N];
ll qpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return res;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
  inv[N - 1] = qpow(fac[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll C(int n, int m) {
  if (n < m) return 0;
  return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
  init();
  // 输出 10 以内的组合数
  // 双层循环输出 10 以内的组合数，直接输出答案，所有 n 一行，m 一列
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j <= i; j++) {
      cout << C(i, j) << " ";
    }
    cout << endl;
  }
  return 0;
}