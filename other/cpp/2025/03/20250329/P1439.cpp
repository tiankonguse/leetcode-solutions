/*
# P1439 【模板】最长公共子序列

## 题目描述

给出 $1,2,\ldots,n$ 的两个排列 $P_1$ 和 $P_2$ ，求它们的最长公共子序列。

## 输入格式

第一行是一个数 $n$。

接下来两行，每行为 $n$ 个数，为自然数 $1,2,\ldots,n$ 的一个排列。

## 输出格式

一个数，即最长公共子序列的长度。

## 输入输出样例 #1

### 输入 #1

```
5
3 2 1 4 5
1 2 3 4 5
```

### 输出 #1

```
3
```

## 说明/提示

- 对于 $50\%$ 的数据， $n \le 10^3$；
- 对于 $100\%$ 的数据， $n \le 10^5$。
*/
#include <bits/stdc++.h>
using namespace std;
int str1[1001], str2[1001];
int dp[1001][1001];  // dp[i][j]表示以str1[i-1]和str2[j-1]结尾的最长公共子串的长度
int maxLen = 0;
int lcsLength(int i, int j) {
  if (dp[i][j] != -1)  // 避免重复计算
    return dp[i][j];
  // 初始化边界条件
  if (i == 0 || j == 0) return 0;  // 边界条件：空字符串和任意字符串的公共子序列长度为0
  // 状态转移方程
  else {
    if (str1[i - 1] == str2[j - 1]) {
      dp[i][j] = lcsLength(i - 1, j - 1) + 1;
    } else {
      dp[i][j] = max(lcsLength(i - 1, j), lcsLength(i, j - 1));
    }
  }
  return dp[i][j];
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &str1[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &str2[i]);
  }

  memset(dp, -1, sizeof(dp));  // 表示未计算

  // 递归计算公共子序列的长度
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int cur = lcsLength(i, j);  // 计算以
      if (cur > maxLen) {
        maxLen = cur;
      }
    }
  }
  printf("%d\n", maxLen);
  return 0;
}

struct Point {
  int x;
  int y;
  void SetPoint(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }
};
vector<vector<Point>> path;
vector<vector<int>> dp;
// 定义函数
int max_sum(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i == n - 1) {  // 边界条件
    dp[i][j] = a[i][j];
    return dp[i][j];
  } else {                           // 表示当前状态没有计算过
    int f1 = max_sum(i + 1, j);      // 递归调用
    int f2 = max_sum(i + 1, j + 1);  // 递归调用/*  */
    // dp[i][j] = max(f1, f2) + a[i][j];
    if (f1 > f2) {
      dp[i][j] = f1 + a[i][j];
      path[i][j].SetPoint(i + 1, j);
    } else {
      dp[i][j] = f2 + a[i][j];
      path[i][j].SetPoint(i + 1, j + 1);
    }
    return dp[i][j];
  }
}

vector<Point> get_path() {
  int i = 0, j = 0;
  vector<Point> result;
  result.push_back(Point{i, j});
  while (i < n - 1) {
    result.push_back(path[i][j]);
    i = path[i][j].x;
    j = path[i][j].y;
  }
  return result;
}