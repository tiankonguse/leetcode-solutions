#include <math.h> /* log2 */
#include <stdarg.h>

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
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
  for (int j = 1; j <= k; j++) {                   // 注意填充的顺序，保证当前状态之前的状态值都计算出来
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
  while (~scanf("%d", &n)) {
    if (n == 0) break;
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

      // 计算左侧相同值的频率
      int leftFreq = t - l;

      // 如果 t > r，说明整个区间 [l, r] 的值都相同
      int maxFreq = leftFreq;
      if (t <= r) {
        maxFreq = max(maxFreq, RMQ(t, r));
      }

      printf("%d\n", maxFreq);
    }
  }

  return 0;
}
/*
6 3
1 7 3 4 2 5
1 5
4 6
2 2



6
3
0
*/
