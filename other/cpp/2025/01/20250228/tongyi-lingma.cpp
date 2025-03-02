// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, MOD = 1e9 + 7;
int fac[N], inv[N], ifac[N];

int qp(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % MOD;
    a = 1ll * a * a % MOD;
  }
  return res;
}

void init() {
  fac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i % MOD;
  inv[N - 1] = qp(fac[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; i--) inv[i] = 1ll * inv[i + 1] * (i + 1) % MOD;
  ifac[0] = 1;
  for (int i = 1; i < N; i++) ifac[i] = 1ll * ifac[i - 1] * inv[i] % MOD;
}

int C(int n, int m) {
  if (n < m) return 0;
  return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

int main() {
  init();
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF) {
    if (n < m) {
      printf("0\n");
      continue;
    }
    printf("%d\n", C(n, m));
  }
  return 0;
}