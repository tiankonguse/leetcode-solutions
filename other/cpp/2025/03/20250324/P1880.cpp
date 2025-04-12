/*
https://www.luogu.com.cn/problem/P1880

# P1880 [NOI1995] 石子合并

## 题目描述

在一个圆形操场的四周摆放 $N$ 堆石子，现要将石子有次序地合并成一堆，规定每次只能选相邻的 $2$
堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。

试设计出一个算法,计算出将 $N$ 堆石子合并成 $1$ 堆的最小得分和最大得分。

## 输入格式

数据的第 $1$ 行是正整数 $N$，表示有 $N$ 堆石子。

第 $2$ 行有 $N$ 个整数，第 $i$ 个整数 $a_i$ 表示第 $i$ 堆石子的个数。

## 输出格式

输出共 $2$ 行，第 $1$ 行为最小得分，第 $2$ 行为最大得分。

## 输入输出样例 #1

### 输入 #1

```
4
4 5 9 4
```

### 输出 #1

```
43
54
```

## 说明/提示

$1\leq N\leq 100$，$0\leq a_i\leq 20$。
*/

#include <bits/stdc++.h>
using namespace std;
int n;
int a[101], dpMin[101][101];
int s[101] = {0};  // 存储前缀和

int min_sum(int a[]) {
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
    dpMin[i][i] = 0;
  }
  // 动态规划
  for (int lenth = 2; lenth <= n; lenth++) {                 // 枚举长度
    for (int i = 1; i + lenth - 1 <= n; i++) {               // 枚举起点
      int j = i + lenth - 1;                                 // 终点
      int cost = s[j] - s[i - 1];                            // 台杂需要付出的代份
      for (int k = i; k < j; k++) {                          // 枚举分割点
        dpMin[i][j] = min(dpMin[i][j], dpMin[i][k]) + cost;  // 更新dp[i][j]
      }
    }
  }
  return dpMin[1][n];
}

int main() {
  scanf("%d", &n);                // 输入石头数量
  for (int i = 1; i <= n; i++) {  // 输入每个石头的值
    scanf("%d", &a[i]);
  }
  int ans = min_sum(a);  // 计算1到n的最小合并代价
  printf("%d\n", ans);
  return 0;
}