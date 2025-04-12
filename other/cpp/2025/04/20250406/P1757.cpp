#include <bits/stdc++.h>
using namespace std;
const int maxzu = 105;
const int maxnum = 1005;
const int maxcap = 1005;
int m, n, t;
long long dp[maxzu][maxcap];
long long w[maxzu][maxnum];  // 重量改为long long
long long c[maxzu][maxnum];  // 价值改为long long
int s[maxzu];

long long maxvalue(int i, int j) {
  if (i <= 0 || j < 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  dp[i][j] = maxvalue(i - 1, j);  // 不选第i组

  for (int k = 0; k < s[i - 1]; k++) {
    if (w[i - 1][k] <= j) {
      long long val = maxvalue(i - 1, j - w[i - 1][k]) + c[i - 1][k];
      if (val > dp[i][j]) {
        dp[i][j] = val;
      }
    }
  }
  return dp[i][j];
}/*  */

int main() {
  memset(dp, -1, sizeof(dp));
  memset(s, 0, sizeof(s));
  scanf("%d %d", &m, &n);
  int no;
  long long a, b;  // 输入变量改为long long
  t = 0;
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld %d", &a, &b, &no);
    no++;
    if (no > t) t = no;
    w[no - 1][s[no - 1]] = a;
    c[no - 1][s[no - 1]] = b;
    s[no - 1]++;
  }
  long long ans = maxvalue(t, m);
  printf("%lld\n", ans);  // 使用%lld输出
  return 0;
}