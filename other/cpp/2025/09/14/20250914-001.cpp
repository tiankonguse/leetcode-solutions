// prim 算法求最小生成树

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;  // 最大节点数
#define INF 0x3f3f3f3f
vector<vector<pair<int, int>>> c;  // 图的邻接表
bool vis[MAXN];                    // 标记结点是否已经访问过
int lowcost[MAXN], closest[MAXN];

void Prim(int n) {
  // 初始状态
  vis[1] = true;  // 假定从结点1开始
  for (int i = 1; i <= n; i++) {
    if (i != 1) {
      lowcost[i] = c[1][i].second;  // 统一使用INF宏，避免与INT_MAX混用
      closest[i] = 1;
      vis[i] = false;
    } else {
      lowcost[i] = 0;
    }
  }

  // 在集合V-U中开始查找距离U最近的结点t,只需要循环n-1次
  for (int i = 1; i < n; i++) {
    int temp = INF;                 // 最小权值
    int t = -1;                     // 最邻近结点编号，初始化为-1表示未找到
    for (int j = 1; j <= n; j++) {  // 找到最邻近的点
      if (!vis[j] && (lowcost[j] < temp)) {
        t = j;
        temp = lowcost[j];
      }
    }

    if (t == -1) {  // 找不到邻近结点t，图不连通
      printf("\n图不连通，无法构建最小生成树\n");
      return;
    }

    vis[t] = true;  // 把找到的邻近结点加入集合U
    printf("%d-->%d, 权值为%d\n", closest[t], t, temp);

    // 更新与t相邻的节点的lowcost和closet数组
    for (auto &e : c[t]) {
      int v = e.first;
      int w = e.second;
      if (!vis[v] && (w < lowcost[v])) {
        lowcost[v] = w;
        closest[v] = t;
      }
    }
  }
}

int main() {
  int n, m;
  printf("请输入节点数和边数: ");
  scanf("%d%d", &n, &m);

  // 关键修复：初始化邻接表大小
  c.resize(n + 1);  // 节点编号从1开始，需要n+1个空间

  printf("请输入 %d 条边(u v w)，其中w为权重:\n", m);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    c[u].push_back({v, w});  // 创建邻接表
    c[v].push_back({u, w});  // 创建邻接表
  }

  Prim(n);
  return 0;
}