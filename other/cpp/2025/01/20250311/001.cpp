/*
# P1923 【深基9.例4】求第 k 小的数

## 题目描述

输入 $n$（$1 \le n < 5000000$ 且 $n$ 为奇数）个数字 $a_i$（$1 \le a_i < {10}^9$），输出这些数字的第 $k$
小的数。最小的数是第 $0$ 小。

请尽量不要使用 `nth_element` 来写本题，因为本题的重点在于练习分治算法。

## 输入格式

无

## 输出格式

无

## 输入输出样例 #1

### 输入 #1

```
5 1
4 3 2 1 5
```

### 输出 #1

```
2
```
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
int a[N];
int n, k;
int part(int a[], int left, int right) {
  // 随机选择基准避免最坏情况
  int random_pivot = left + rand() % (right - left + 1);
  swap(a[left], a[random_pivot]);

  int i = left;
  int j = right;
  while (i < j) {
    while (i < j && a[j] >= a[left]) j--;
    while (i < j && a[i] <= a[left]) i++;
    swap(a[i], a[j]);
  }
  swap(a[left], a[i]);
  return i;
}
void quickselect(int a[], int left, int right) {
  int p = part(a, left, right);  // 找到基准
  if (k < p)
    quickselect(a, left, p - 1);
  else if (k > p)
    quickselect(a, p + 1, right);
  else {
    printf("%d", a[k]);
    exit(0);
  }
}
int main() {
//   srand(time(0));
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  quickselect(a, 0, n - 1);
  // printf("%d\n",a[k]);
  return 0;
}