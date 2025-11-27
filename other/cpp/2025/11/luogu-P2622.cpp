// https://www.luogu.com.cn/problem/P2622

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e8;
int n, m;                   // n个灯m个按钮
vector<vector<int>> buton;  // 存储每个按钮
vector<int> cur;            // 按钮是否按下的所有状态
vector<vector<int>> all;    // 按钮是否按下的所有状态
vector<int> light;          // 灯的状态
void dfs() {
  if (cur.size() == m) {  // 递归出口：所有按钮的状态都生成完
    all.push_back(cur);   // 把当前序列存储
    return;
  }
  for (int i = 0; i <= 1; i++) {  // 只有0或者1的状态
    cur.push_back(1 - i);
    dfs();
    cur.pop_back();
  }
}
bool cmp(const vector<int> &a, const vector<int> &b) {
  int cnt1 = count(a.begin(), a.end(), 1);  // 统计vector中1的个数
  int cnt2 = count(b.begin(), b.end(), 1);
  if (cnt1 != cnt2) {
    return cnt1 < cnt2;  // 次数少的在前面
  }
  return a < b;  // 就按照字典升序
}
bool alloff(const vector<vector<int>> &all, int i) {
  light.resize(n, 1);  // 灯的初始状态
  int c1, c2;
  for (int k = 0; k < n; k++) {    // 遍历每一个灯
    c1 = 0;                        // 统计1的个数
    c2 = 0;                        // 统计-1的个数
    bool flag = false;             // 每个灯假如不能关闭
    for (int j = 0; j < m; j++) {  // 遍历当前序列中按钮的状态
      if (all[i][j] == 1) {        // 当前按钮被按下
        if (buton[j][k] == 1) {
          c1++;

        } else if (buton[j][k] == -1) {
          c2++;
        }
      }
    }
    // 判断当前第k个灯是否能关闭
    printf("第 %d 个灯：i=%d c1=%d c2=%d\n", k, i, c1, c2);
    if (c1 >= c2) {
      flag = true;
    } else {
      //   return false;  // 只要有一盏灯不能关都不成立
    }
  }
  return true;  // 所有灯都能关闭就说明可以
}
int main() {
  scanf("%d%d", &n, &m);
  buton.resize(m, vector<int>(n));  // 初始化按钮
  // 输入按钮的控制状态
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &buton[i][j]);
    }
  }

  dfs();  // 生成按钮的所有状态

  // 针对按钮的每一个状态模拟判断
  for (int i = 0; i < all.size(); i++) {
    printf("第 %d 组：", i);
    for (int j = 0; j < all[i].size(); j++) {
      printf("%d ", all[i][j]);
    }
    printf("\n");
    if (alloff(all, i)) {                               // 对于每个按钮序列，如果能关闭全部灯
      int ct = count(all[i].begin(), all[i].end(), 1);  // 统计1的个数
      printf("%d\n", ct);
      //   return 0;  // 结束程序
    }
  }
  // 当所有按钮组合都不能关闭所有灯时
  printf("-1\n");
  return 0;
}
/*
【输入样例】
3
2
1 0 1
-1 1 0
【输出样例】
2



*/
