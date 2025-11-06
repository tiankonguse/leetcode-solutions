const int N = 505;
int n, m, c[N], a[N], pre[N];
char s[N];
mint fac[N], ifac[N], dp[N][N][N];
mint A(int n, int m) { return n < m ? 0 : fac[n] * ifac[n - m]; }
mint C(int n, int m) { return n < m ? 0 : fac[n] * ifac[m] * ifac[n - m]; }

mint dfs(int i, int j, int k) {
  // 填到第i位，死亡j人，已经填完的人中耐心够的有k个
  if (dp[i][j][k].val != -1) return dp[i][j][k];
  if (i > n) return dp[i][j][k] = (j <= n - m && k == n - pre[j]) ? fac[k] : 0;
  mint res = 0;
  if (s[i] == '1') {
    int x = i - 1 - k;
    if (pre[j] >= x) {  // 1. 选择 c <= j 的人，此人因耐心不够死亡
      for (int p = 0; p <= min(k, a[j + 1]); p++) {
        res += dfs(i + 1, j + 1, k - p) * C(a[j + 1], p) * A(k, p) * (pre[j] - x);
      }
    }
    // 2.选择 c > j 的人，该人存活，且 k -> k + 1
    res += dfs(i + 1, j, k + 1);
  } else {
    // 1. 选择 c <= j + 1 的人，该人死亡，j -> j + 1
    for (int p = 0; p <= min(k, a[j + 1]); p++) {
      int x = (i - 1) - (k - p);
      if (pre[j + 1] < x) continue;
      res += dfs(i + 1, j + 1, k - p) * C(a[j + 1], p) * A(k, p) * (pre[j + 1] - x);
    }
    // 2. 选择 c > j + 1 的人，该人死亡，j -> j + 1, k -> k - p + 1
    for (int p = 0; p <= min(k, a[j + 1]); p++) {
      res += dfs(i + 1, j + 1, k - p + 1) * C(a[j + 1], p) * A(k, p);
    }
  }
  return dp[i][j][k] = res;
}

void _main() {
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i, ifac[i] = ~fac[i];
  cin >> n >> m >> (s + 1);
  for (int i = 1; i <= n; i++) cin >> c[i], a[c[i]]++;
  pre[0] = a[0];
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
  memset(dp, -1, sizeof(dp));
  cout << dfs(1, 0, 0);
}
