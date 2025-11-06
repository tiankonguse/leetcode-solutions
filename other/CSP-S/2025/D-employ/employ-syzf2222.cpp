#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
#define inf 1e9
inline int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + c - '0';
    c = getchar();
  }
  return x * f;
}
const int N = 505;
int n, m, dp[N][N], c[N], pre[N], a[N], op[N], C[N][N], fac[N], ans, tmp[N][N];
string S;
inline void add(int &x, int y) { x = (x + y >= mod ? x + y - mod : x + y); }
int main() {
  freopen("swefp.in", "r", stdin);
  freopen("swefp.ans", "w", stdout);
  n = read(), m = read();
  cin >> S;
  for (int i = 1; i <= n; i++) a[i] = read(), c[a[i]]++;
  pre[0] = c[0];
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + c[i];
  for (int i = 1; i <= n; i++) op[i] = S[i - 1] - '0';
  //	for(int i=1;i<=n;i++)
  //		printf("%d ",op[i]);puts("");
  //	for(int i=0;i<=n;i++)
  //		printf("%d ",c[i]);puts("");
  //	printf("n=%d m=%d\n",n,m);
  C[0][0] = fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    fac[i] = 1ll * i * fac[i - 1] % mod;
    for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  }
  //	for(int i=1;i<=n;i++)
  //		printf("%d ",op[i]);puts("");
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++)
      for (int k = 0; k <= pre[j] && k <= i; k++)
        if (op[i + 1]) {
          if (n - pre[j] > i - k) add(tmp[j][k], dp[j][k]);
          for (int l = 0; l <= c[j + 1] && l <= i - k; l++)
            add(tmp[j + 1][k + l + 1],
                1ll * C[c[j + 1]][l] * C[i - k][l] % mod * fac[l] % mod * (pre[j] - k) % mod * dp[j][k] % mod);
        } else {
          for (int l = 0; l <= c[j + 1] && l <= i - k; l++) {
            if (n - pre[j + 1] > i - k - l)
              add(tmp[j + 1][k + l], 1ll * C[c[j + 1]][l] * C[i - k][l] % mod * fac[l] % mod * dp[j][k] % mod);
            add(tmp[j + 1][k + l + 1],
                1ll * C[c[j + 1]][l] * C[i - k][l] % mod * fac[l] % mod * (pre[j + 1] - k - l) % mod * dp[j][k] % mod);
          }
        }
    for (int j = 0; j <= n; j++)
      for (int k = 0; k <= n; k++) dp[j][k] = tmp[j][k], tmp[j][k] = 0;
    //		for(int j=0;j<=i+1;j++)
    //			for(int k=0;k<=pre[j]&&k<=i+1;k++)
    //				printf("dp[%d][%d][%d]=%d\n",i+1,j,k,dp[j][k]);
  }
  for (int i = 0; n - i >= m; i++) add(ans, 1ll * dp[i][pre[i]] * fac[n - pre[i]] % mod);
  printf("%d\n", ans);
  return 0;
}
/*
3 2
1 1 2
101
*/
