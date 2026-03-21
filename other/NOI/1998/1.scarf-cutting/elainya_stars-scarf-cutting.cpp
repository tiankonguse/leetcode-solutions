#include <bits/stdc++.h>
using namespace std;

const int N = 205;  // 开够
int n, m, dp[N][N], temp[N][N], ans;

void cal() {
  for (int i = n - 1; i >= 1; i--)
    for (int j = 1; j < i * 2; j += 2)
      if (dp[i][j] > 0 && dp[i + 1][j] > 0 && dp[i + 1][j + 1] > 0 && dp[i + 1][j + 2] > 0)
        dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 2]) + 1;
  for (int i = 2; i <= n; i++)
    for (int j = 4; j < (i - 1) * 2; j += 2)
      if (dp[i][j] > 0 && dp[i - 1][j - 2] > 0 && dp[i - 1][j - 1] > 0 && dp[i - 1][j] > 0)
        dp[i][j] = min(dp[i - 1][j - 2], dp[i - 1][j]) + 1;
  for (int i = 1; i <= n; i++) {
    int ans1 = 0, ans2 = 0;
    for (int j = 1; j <= i; j++) {
      for (int k = 1; k < j * 2; k += 2) ans1 = max(ans1, min(i - j + 1, dp[j][k]));
      for (int k = 2; k < j * 2; k += 2) ans1 = max(ans1, dp[j][k]);
    }
    for (int j = i + 1; j <= n; j++) {
      for (int k = 1; k < j * 2; k += 2) ans2 = max(ans2, dp[j][k]);
      for (int k = 2; k < j * 2; k += 2) ans2 = max(ans2, min(j - (i + 1) + 1, dp[j][k]));
    }
    if (ans1 && ans2)                             // 一定不是0，如果是0的话说明分割线上或下找不到三角形
      ans = max(ans, ans1 * ans1 + ans2 * ans2);  // 注意让输出的是面积不是边长
  }
}

void spin120() {
  memset(temp, 0, sizeof temp);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i * 2; j += 2) temp[n - (j + 1) / 2 + 1][i * 2 - j] = (dp[i][j] == 0 ? 0 : 1);  // 要存原始的值
    for (int j = 2; j < i * 2; j += 2) temp[n - j / 2 + 1][i * 2 - j] = (dp[i][j] == 0 ? 0 : 1);
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i * 2; j++) dp[i][j] = temp[i][j];
}

signed main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j < i * 2; j++) dp[i][j] = 1;
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d%d", &x, &y);
    dp[x][y] = 0;
    // while (1) puts("no ctjing");
  }
  cal();
  spin120();
  //	for(int i=1;i<=n;i++)
  //	{
  //		for(int j=1;j<i*2;j++)
  //		  printf("%d ",dp[i][j]);
  //		puts("");
  //	}
  cal();
  spin120();  // 转两次
  cal();
  printf("%d\n", ans);
  return 0;
}
