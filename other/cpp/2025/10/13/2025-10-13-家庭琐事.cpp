/*

（POJ1949家庭琐事）有一份必须完成的n个家务的清单（3<=n<=10000）,每个家务都需要一个整数时间t（1<=t<=100)才能完成，并且可能还有其他家务必须在某家务开始之前完成。第1个家务没有先决条件，家务K（K>1)只能以家务1到K-1为先决条件。计算完成所有家务所需的最短时间。当然，可以同时进行彼此没有依赖关系的家务。
【输入】第1行为整数n，第2到n+1行描述每个家务。每行都包含完成家务的时间，先决条件的数量Pi(0<=Pi<=100)和Pi个先决条件。
【输出】单行输出完成所有家务所需的最短时间
【输入样例】
7
5 0
1 1 1
3 1 2
6 1 1
1 2 2 4
8 2 2 4
4 3 3 5 6
【输出样例】
23
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int MAXN = 10005;

// int times[MAXN];  // 存储每个家务的时间
// 邻接表表示图 (u -> v 表示u是v的先决条件)
// vector<vector<int> > adj(MAXN);
// 入度数组
// int inDegree[MAXN];
// 拓扑排序
// int topo[MAXN];

stack<int> q;
int main() {
  int n;
  scanf("%d", &n);

  vector<int> times(n + 1, 0);  // 存储每个家务的时间

// 邻接表表示图 (u -> v 表示u是v的先决条件)
  vector<vector<int> > adj(n + 1);

  // 入度数组
  vector<int> inDegree(n + 1, 0);
  // 拓扑排序
  vector<int> topo(n + 1, 0);

  // 输入数据并构建图
  for (int i = 1; i <= n; i++) {
    int t, p;
    scanf("%d%d", &t, &p);
    times[i] = t;

    // 读取p个先决条件，构建有向边: pre -> i
    for (int j = 1; j <= p; j++) {
      int pre;
      scanf("%d", &pre);
      adj[pre].push_back(i);  // 先决条件指向当前任务
      inDegree[i]++;          // 增加当前任务的入度
    }
  }

  // 起点入栈（入度为0的节点）
  for (int i = 1; i <= n; i++) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }
  int k = 1;
  // 执行拓扑排序
  while (!q.empty()) {
    int u = q.top();
    q.pop();
    topo[k++] = u;
    // 处理所有后继节点
    for (int i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }

  // 计算最早开始时间和最早完成时间
  //   int ve[MAXN] = {0};
  vector<int> ve(n + 1, 0);  // 最早完成时间

   ve[1] = times[1]; // 第一个任务的最早完成时间就是它自己的时间
  for (int i = 1; i <= n; i++) {
    int u = topo[i];
    cout << i << " " << u << endl;
    for (int j = 0; j < adj[u].size(); j++) {
      int v = adj[u][j];
      // v的最早完成时间 = max(v当前最早完成时间, u的最早完成时间 + v的时间)
      if (ve[v] < ve[u] + times[v]) {
        ve[v] = ve[u] + times[v];
        cout << "u update v: " << v << " " << ve[v] << endl;
      }
    }
  }

  // 关键路径长度就是最后一个任务的最早完成时间
  int maxTime = 0;
  for (int i = 1; i <= n; i++) {
    maxTime = max(maxTime, ve[i]);
  }
  cout << maxTime << endl;

  return 0;
}
