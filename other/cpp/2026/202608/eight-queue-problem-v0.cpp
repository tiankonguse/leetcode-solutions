#include <bits/stdc++.h>
using namespace std;

int ans = 0;
bool col[9];
bool dia1, dia2;
void dfs(int row) {
  if (row == 8) {
    ans++;
    return;
  }
  // 问题1： 行从  0 开始，列从 1 开始
  for (int c = 0; c < 8; c++) {
    int d1 = c - row;
    int d2 = c + row - 7;
    if (!col[c]) continue;
    if (d1 == 0 && !dia1) continue;
    if (d2 == 0 && !dia2) continue;

    // 问题2： 正斜线与反斜线分别只有一条
    col[c] = false;
    if (d1 == 0) dia1 = false;
    if (d2 == 0) dia2 = false;
    dfs(row + 1);
    col[c] = true;
    if (d1 == 0) dia1 = true;
    if (d2 == 0) dia2 = true;
  }
}
int main() {
  int a;
  scanf("%d", &a);
  fill(col, col + 9, true);
  dia1 = true;
  dia2 = true;
  //   fill(dia1, dia1 + 16, true);
  //   fill(dia2, dia2 + 16, true);
  dfs(0);
  printf("%d\n", ans);
  return 0;
}
