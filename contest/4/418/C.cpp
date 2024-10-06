// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define myDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  vector<vector<int>> constructGridLayout(const int n,
                                          vector<vector<int>>& edges) {
    // 度数分布： 顶点度数为 2， 边度数为 3， 内部顶点度数为 4
    vector<vector<int>> g(n);
    for (auto& v : edges) {
      int a = v[0], b = v[1];
      g[a].push_back(b);
      g[b].push_back(a);
    }
    int minDeg = 0;
    for (int i = 0; i < n; i++) {
      myDebug("i=%d deg=%d\n", i, g[i].size());
      if (g[i].size() < g[minDeg].size()) {
        minDeg = i;  // 找到一个角
      }
    }
    vector<int> rows;
    rows.reserve(n);

    // 分三种情况： 1*b, 2*b, a*b
    if (g[minDeg].size() == 1) {  // 1*b
      rows.push_back(minDeg);
      myprintf("1*b: %d[%d], finish,N=%d\n", minDeg, g[minDeg].size(),
               rows.size());
    } else {
      if (g[g[minDeg][0]].size() > g[g[minDeg][1]].size()) {
        swap(g[minDeg][0], g[minDeg][1]);
      }
      if (g[g[minDeg][0]].size() == 2) {  // 2 * b
        rows.push_back(minDeg);
        myprintf("2*b: %d[%d]", minDeg, g[minDeg].size());

        int b = g[minDeg][0];
        rows.push_back(b);
        myprintf("%d[%d], finish,N=%d\n", b, g[b].size(), rows.size());
      } else {  // a*b
        int now = minDeg;
        rows.push_back(now);
        int pre = -1;
        myprintf("a*b: %d[%d]", now, g[now].size());
        while (1) {
          for (int b : g[now]) {
            if (b == pre) continue;
            if (g[b].size() == 4) continue;
            myprintf("->%d[%d]", b, g[b].size());
            rows.push_back(b);
            pre = now;
            now = b;
            break;
          }
          if (g[now].size() == 2) {  // 结束了
            myprintf(" , finish, N=%d \n", rows.size());
            break;
          }
        }
      }
    }
    int N = rows.size();
    int M = n / N;
    vector<vector<int>> ans(N, vector<int>(M, 0));
    vector<int> flag(n, 0);

    for (int i = 0; i < N; i++) {
      ans[i][0] = rows[i];
      flag[rows[i]] = 1;
    }

    for (int i = 1; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int pre0 = ans[j][i - 1];
        for (auto b : g[pre0]) {
          if (flag[b]) continue;
          ans[j][i] = b;
          flag[b] = 1;
          break;
        }
      }
    }
    return ans;
  }
};

/*
12
[[0,1],[0,3],[0,6],[0,8],[1,5],[1,9],[2,3],[2,10],[2,11],[3,5],[3,7],[4,6],[4,8],[5,10],[6,7],[7,11],[8,9]]

[[4,8,9,0]
,[6,0,1,5]
,[7,3,2,10]]

[[11,2,10]
,[7,3,5]
,[6,0,1]
,[4,8,9]]
*/
