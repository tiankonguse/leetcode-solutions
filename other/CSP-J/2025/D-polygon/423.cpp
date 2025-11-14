

namespace MAIN {
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e3 + 5, mod = 998244353;
int n, a[N], maxn, dp[N][N], sum[N][N], sum2[N][N];
signed Main() {
  // freopen("polygon.in", "r", stdin);
  // freopen("polygon.out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    maxn = max(maxn, a[i]);
  }
  ++maxn;
  sort(a + 1, a + n + 1);
  dp[1][a[1]] = 1;
  ++dp[2][a[2]];
  ++dp[2][min(maxn, a[1] + a[2])];
  ++dp[3][a[3]];
  ++dp[3][min(maxn, a[1] + a[3])], ++dp[3][min(maxn, a[2] + a[3])];
  ++dp[3][min(maxn, a[1] + a[2] + a[3])];
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= maxn + 1; ++j) {
      sum[i][j] = sum[i][j - 1] + dp[i][j];
      sum2[i][j] = sum2[i - 1][j] + dp[i][j];
    }
  }
  for (int i = 4; i <= n; ++i) {
    ++dp[i][a[i]];
    for (int j = 1; j <= maxn + 1; ++j) {
      if (j != maxn + 1) (dp[i][min(maxn, a[i] + j)] += sum2[i - 1][j]) %= mod;
      sum[i][j] = (sum[i][j - 1] + dp[i][j]) % mod;
      sum2[i][j] = (sum2[i - 1][j] + dp[i][j]) % mod;
    }
  }
  int ans = 0;
  for (int i = 3; i <= n; ++i) {
    for (int j = 2; j < i; ++j) {
      (ans += (sum[j][maxn + 1] - sum[j][a[i]]) % mod) %= mod;
    }
  }
  cout << ans;
  return 0;
}
}  // namespace MAIN