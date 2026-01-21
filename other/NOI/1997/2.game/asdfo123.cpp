#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 110;
int a[N][5], ans;
int dp[N][N][5], n, m;
int x1, yy1, x2, y2;  // 用dp[i][j][l]表示第i堆第j块积木第l条边的最大高度
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);  // a[i][k+2]是这面所对应的高
    a[i][3] = a[i][0];
    a[i][4] = a[i][1];
  }
  for (int i = 1; i <= m; i++)          // 第i根柱子
    for (int j = 1; j <= n; j++)        // 第j块积木
      for (int h = 0; h < j; h++)       // 在编号小的积木中找第h块积木 (从0开始,否则求不出1的值)
        for (int k = 0; k <= 2; k++)    // 第h块积木的第k条边
          for (int l = 0; l <= 2; l++)  // 第j块积木的第l条边
          {
            x1 = max(a[h][k], a[h][k + 1]);                                 // 下面积木上表面的长边
            yy1 = min(a[h][k], a[h][k + 1]);                                // 短边
            x2 = max(a[j][l], a[j][l + 1]);                                 // 上面积木下表面的长边
            y2 = min(a[j][l], a[j][l + 1]);                                 // 短边
            if (x1 >= x2 && yy1 >= y2)                                      // 如果下面积木的两条边大于上面积木的两边
              dp[i][j][l] = max(dp[i][j][l], dp[i][h][k] + a[j][l + 2]);    // 放或不放，取较大佱
            dp[i][j][l] = max(dp[i][j][l], dp[i - 1][h][k] + a[j][l + 2]);  // 和前一堆比较
            ans = max(ans, dp[i][j][l]);
          }
  printf("%d", ans);
  return 0;
}
