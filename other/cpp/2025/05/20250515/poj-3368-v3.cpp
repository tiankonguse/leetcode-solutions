#include <math.h>

#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 100001;
int F[N][20];
int a[N], cnt[N], n, q, k, l, r;
// 预处理cnt数组
void init() {
  for (int i = 1; i <= n; i++) {
    if (i == 1) {
      cnt[i] = 1;
    } else {
      if (a[i] == a[i - 1]) {
        cnt[i] = cnt[i - 1] + 1;
      } else {
        cnt[i] = 1;
      }
    }
  }
}
// 创建ST表
void creat_ST() {
  // 初始化边界
  for (int i = 1; i <= n; i++) {
    F[i][0] = cnt[i];
  }
  // j从1开始填充
  for (int j = 1; j <= k; j++) {  // 注意填充的顺序，保证当前状态之前的状态值都计算出来
    for (int i = 1; i <= n - (1 << j) + 1; i++) {  // n-2^j+1
      F[i][j] = max(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
    }
  }
}

// 查询区间最值
int RMQ(int L, int R) {
  int j = (int)log2(R - L + 1);
  int m = max(F[L][j], F[R - (1 << j) + 1][j]);
  return m;
}
int main() {
  while (scanf("%d", &n) && n) {
    scanf("%d", &q);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    k = log2(n);  // 或者log(n)/log(2);
    init();
    creat_ST();  // 创建ST表
    for (int i = 1; i <= q; i++) {
      scanf("%d%d", &l, &r);
      int t = l;
      while (t <= r && a[t] == a[l]) {
        t++;
      }
      // 如果此时t>r,则说明[l,r]区间完全都是相同的数字
      int ans = t - l;
      if (t <= r) {
        ans = max(ans, RMQ(t, r));  // 求区间[l,r]之间胡最大值和最小值的差
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
/*
【输入样例】
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10
0

【输出样例】
1
4
3
*/