#include <bits/stdc++.h>
using namespace std;
int a[5005];
int n;
int maxlen[5005];
int maxsublenth(int i) {
  if (maxlen[i] != -1)  // 避免重复计算
    return maxlen[i];
  // 初始化边界条件
  if (maxlen[i] == -1) {
    maxlen[i] = 1;
  }
  // 递归调用，实现状态转移方程
  for (int j = 0; j < i; j++) {
    if (a[i] > a[j]) {
      int templenth = maxsublenth(j) + 1;
      if (templenth > maxlen[i]) {
        maxlen[i] = templenth;  // 更新最大长度
      }
    }
  }

  return maxlen[i];
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    maxlen[i] = -1;  // 表示未计算
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int curlenth = maxsublenth(i);
    if (curlenth > ans) {
      ans = curlenth;
    }
  }
  printf("%d\n", ans);
  return 0;
}