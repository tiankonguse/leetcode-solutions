#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> M;  // 邻接矩阵
// 打印邻接矩阵
void PrintVertex() {
  for (int i = 0; i < n; i++) {  // 顶点的个数
    for (int j = 0; j < n; j++) {
      printf("%d ", M[i][j]);
    }
    printf("\n");  // 每一行换行
  }
}
int main() {
  int x, y;
  scanf("%d %d", &n, &m);
  M.resize(n, vector<int>(n, 0));  // 初始化邻接矩阵大小
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &x, &y);
    M[x][y] = 1;
    M[y][x] = 1;
  }
  printf("最初邻接矩阵为：\n");
  PrintVertex();  // 输出邻接矩阵
  return 0;
}

/*
5 7
0 1
0 2
0 3
1 2
2 3
2 4
4 3
*/