#include <bits/stdc++.h>
using namespace std;
int n, m;
char a[101][101];  // 存储每个格子情况
char b[101][101];  // 存储结果
int c_num(int i, int j) {
  int ct = 0;                                                    // 地雷格数量
  if (j - 1 >= 0 && a[i][j - 1] == '*') ct++;                    // 上方地雷格子
  if (j + 1 < m && a[i][j + 1] == '*') ct++;                    // 下方地雷格子
  if (i - 1 >= 0 && a[i - 1][j] == '*') ct++;                    // 左方地雷格子
  if (i + 1 < n && a[i + 1][j] == '*') ct++;                    // 右方地雷格子
  if (i - 1 >= 0 && j - 1 >= 0 && a[i - 1][j - 1] == '*') ct++;  // 左上方地雷格子
  if (i - 1 >= 0 && j + 1 < m && a[i - 1][j + 1] == '*') ct++;  // 左下方地雷格子
  if (i + 1 < n && j - 1 >= 0 && a[i + 1][j - 1] == '*') ct++;  // 右上方地雷格子
  if (i + 1 < n && j + 1 < m && a[i + 1][j + 1] == '*') ct++;  // 右下方地雷格子
  return ct;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {  // 以为字符串的形式输入
    scanf("%s", a[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == '*') {
        b[i][j] = '*';
      } else {
        b[i][j] = c_num(i, j) + '0';  // 自定义函数，统计当前位置周边的地雷格子数量
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c", b[i][j]);
    }
    printf("\n");
  }
//   fclose(stdin);
//   fclose(stdout);
  return 0;
}