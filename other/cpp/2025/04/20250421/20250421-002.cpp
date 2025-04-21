#include <bits/stdc++.h>
using namespace std;
int n, m;
// vector<int>v; //顶点集合
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
// 增加边
/*void addEdge(int i, int j) {
 // 索引越界与相等处理
 if (i < 0 || j < 0 || i >= n || j >= n || i == j) {
  printf("顶点不存在\n");
 }
 M[i][j] = 1;
 M[j][i] = 1;
}
// 无向图中参数 i, j 分别表示顶点的索引下标
void removeEdge(int i, int j) {
        // 索引越界与相等处理
if (i < 0 || j < 0 || i >=n || j >= n || i == j) {
       printf("顶点不存在\n");
    }
        M[i][j] = 0;
        M[j][i] = 0;

}
//增加顶点值为val
void addVertex(int val) {  //顶点的值
         n++;
        // 向顶点列表中添加新顶点的值
        v.push_back(val);
        // 在邻接矩阵中添加一行
        M.emplace_back(vector<int>(n, 0));
        // 在邻接矩阵中后面添加一列
        for (int i=0;i<M.size();i++) {
            M[i].push_back(0);
        }
}

void removeVertex(int index) {  //顶点的下标
       n--;
        // 在顶点列表中移除索引 index 的顶点
        v.erase(v.begin() + index);
        // 在邻接矩阵中删除索引 index 的行
        M.erase(M.begin() + index);
        // 在邻接矩阵中删除索引 index 的列
        for (int i=0;i<M.size();i++) {
            M[i].erase(M[i].begin() + index);
        }
}
*/

int main() {
  int x, y;
  scanf("%d%d", &n, &m);
  // v.resize(n); // 初始化顶点集合大小
  M.resize(n, vector<int>(n, 0));  // 初始化邻接矩阵大小
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &x, &y);
    M[x][y] = 1;
    M[y][x] = 1;
  }
  printf("最初邻接矩阵为：\n");
  PrintVertex();  // 输出邻接矩阵

  // 增加顶点1到2的边

  /*addEdge(1,2);
  printf("增加1到2的边后邻接矩阵为：\n");
  PrintVertex(); //输出邻接矩阵

  //删除顶点1到3的边

  removeEdge(1,3);
  printf("删除1到3的边后邻接矩阵为：\n");
  PrintVertex(); //输出邻接矩阵

  //增加顶点6
  addVertex(5);
  printf("增加顶点5后邻接矩阵为：\n");
  PrintVertex(); //输出邻接矩阵

  //删除顶点3
  removeVertex(3);
  printf("删除顶点3后邻接矩阵为：\n");
  PrintVertex(); //输出邻接矩阵
  */
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