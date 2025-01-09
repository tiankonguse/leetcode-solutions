#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int min_num = 10000;
char str[N][N];  // 每一行的颜色字符串
int w[N];        // 存储一行改为白色的格子数量
int b[N];        // 存储一行改为蓝色的格子数量
int r[N];        // 存储一行改为红色的格子数量
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", str[i]);
    for (int j = 0; j < m; j++) {
      if (str[i][j] == 'W') {  // 统计每一行白色的格子数量
        w[i]++;
      }
      if (str[i][j] == 'B') {  // 统计每一行蓝色的格子数量
        b[i]++;
      }
      if (str[i][j] == 'R') {  // 统计每一行宏色的格子数量
        r[i]++;
      }
    }
  }

  // 计算每一行需要改为对应颜色的格子数量
  for (int i = 0; i < n; i++) {
    w[i] = m - w[i];
    b[i] = m - b[i];
    r[i] = m - r[i];
  }
  // 计算从第1行到第n行的改为对应颜色的格子数量的累加和
  for (int i = 1; i < n; i++) {
    w[i] += w[i - 1];
    b[i] += b[i - 1];
    r[i] += r[i - 1];
  }

  // [0, i] [i+1,j] [j+1, n-1]
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      int temp = w[i] + b[j] - b[i] + r[n - 1] - r[j];
      min_num = min(min_num, temp);
    }
  }
  printf("%d\n", min_num);
  return 0;
}