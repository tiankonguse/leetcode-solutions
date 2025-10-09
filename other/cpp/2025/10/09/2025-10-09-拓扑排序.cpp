#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;  // 最大节点数
#define INF 0x3f3f3f3f

vector<vector<int>> e;  // 图的邻接表
int indegree[MAXN];     // 节点的入度
int topo[MAXN];         // 存储拓扑排序
int n, m;
stack<int> s;  // 栈
// 拓扑排序
bool toposort() {
  int k = 0;  // 拓扑序列的下标
  for (int i = 0; i < n; i++) {
    if (indegree[i] == 0) {
      s.push(i);
    }
  }
  while (!s.empty()) {
    int temp = s.top();
    s.pop();                                    // 栈顶元素出栈
    topo[k++] = temp;                           // 栈顶元素存放topo数组
    printf("出栈: %d\n", temp);              // 输出出栈节点
    for (int i = 0; i < e[temp].size(); i++) {  // 遍历temp的所有邻接点
      int v = e[temp][i];
      if (--indegree[v] == 0) {
        s.push(v);
      }
    }
  }
  if (k != n) {  // 说明有环
    return 0;
  }
  return 1;
}

int main() {
  printf("请输入节点数和边数: ");
//   e.clear();
  scanf("%d%d", &n, &m);
  e.resize(n);
  memset(indegree, 0, sizeof(indegree));
  memset(topo, 0, sizeof(topo));
  printf("请输入 %d 条边(u v)\n", m);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    indegree[v]++;  // 累加节点的入度
  }

  // 执行拓扑排序
  if (toposort()) {
    for (int i = 0; i < n; i++) {
      printf("%d ", topo[i]);
    }
    printf("\n");
  } else {
    printf("有环\n");
  }

  return 0;
}

/*

输入
3 3
0 1
1 2
2 0

*/
