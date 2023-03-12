// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  const int CAT = 0, MOUSE = 1;
  const int CAT_WIN = 2, MOUSE_WIN = 1;

  int ans[2][55][55];
  int out_degree[2][55][55];
  queue<tuple<int, int, int>> que;  // 猫必败, 鼠必败是才进队列
  vector<vector<int>> g;

  void CheckCatAllLose(int cat, int mouse_pre) {
    for (auto cat_pre : g[cat]) {
      if (ans[CAT][cat_pre][mouse_pre] != 0) continue;
      out_degree[CAT][cat_pre][mouse_pre]++;
      if (out_degree[CAT][cat_pre][mouse_pre] == g[cat_pre].size()) {
        ans[CAT][cat_pre][mouse_pre] = MOUSE_WIN;
        que.push({CAT, cat_pre, mouse_pre});
      }
    }
  }
  void CheckMouseAllLose(int cat_pre, int mouse) {
    for (auto mouse_pre : g[mouse]) {
      if (ans[MOUSE][cat_pre][mouse_pre] != 0) continue;
      out_degree[MOUSE][cat_pre][mouse_pre]++;
      if (out_degree[MOUSE][cat_pre][mouse_pre] == g[mouse_pre].size()) {
        ans[MOUSE][cat_pre][mouse_pre] = CAT_WIN;
        que.push({MOUSE, cat_pre, mouse_pre});
      }
    }
  }

 public:
  int catMouseGame(vector<vector<int>>& g_) {
    g.swap(g_);

    int n = g.size();
    // printf("n=%d\n", n);
    memset(ans, 0, sizeof(ans));
    memset(out_degree, 0, sizeof(out_degree));

    // 老鼠在洞里，必胜
    for (int cat = 1; cat < n; cat++) {
      int mouse = 0;
      if (ans[CAT][cat][mouse] == 0) {
        ans[CAT][cat][mouse] = MOUSE_WIN;
        // printf("cat(%d,%d) 必败\n", cat, mouse);
        que.push({CAT, cat, mouse});
      }

      if (ans[MOUSE][cat][mouse] == 0) {
        ans[MOUSE][cat][mouse] = MOUSE_WIN;
        // printf("mouse(%d,%d) 必胜\n", cat, mouse);
        CheckCatAllLose(cat, mouse);
      }
    }

    for (int mouse = 1; mouse < n; mouse++) {
      int cat = mouse;
      if (ans[MOUSE][cat][mouse] == 0) {
        ans[MOUSE][cat][mouse] = CAT_WIN;
        // printf("mouse(%d,%d) 必败\n", cat, mouse);
        que.push({MOUSE, cat, mouse});
      }

      if (ans[CAT][cat][mouse] == 0) {
        ans[CAT][cat][mouse] = CAT_WIN;
        // printf("cat(%d,%d) 必胜\n", cat, mouse);
        CheckMouseAllLose(cat, mouse);
      }
    }

    // 猫在老鼠洞里也算输
    for (int mouse = 0; mouse < n; mouse++) {
      int cat = 0;
      if (ans[CAT][cat][mouse] == 0) {
        ans[CAT][cat][mouse] = MOUSE_WIN;
        // printf("cat(%d,%d) 必败\n", cat, mouse);
        que.push({CAT, cat, mouse});
      }

      if (ans[MOUSE][cat][mouse] == 0) {
        ans[MOUSE][cat][mouse] = MOUSE_WIN;
        // printf("mouse(%d,%d) 必胜\n", cat, mouse);
        CheckCatAllLose(cat, mouse);
      }
    }

    while (!que.empty()) {
      auto [t, cat, mouse] = que.front();
      int state = ans[t][cat][mouse];
      que.pop();

      if (t == CAT) {  // 猫必败，所有可到达的顶点都是鼠必胜点
        for (auto mouse_pre : g[mouse]) {
          if (ans[MOUSE][cat][mouse_pre] != 0) continue;
          ans[MOUSE][cat][mouse_pre] = MOUSE_WIN;
          // printf("mouse(%d,%d) 必胜\n", cat, mouse_pre);
          CheckCatAllLose(cat, mouse_pre);
        }
      } else {  // 鼠必败，所有可到达的顶点都是猫必胜点
        for (auto cat_pre : g[cat]) {
          if (ans[CAT][cat_pre][mouse] != 0) continue;
          ans[CAT][cat_pre][mouse] = CAT_WIN;
          // printf("cat(%d,%d) 必胜\n", cat_pre, mouse);
          CheckMouseAllLose(cat_pre, mouse);
        }
      }
    }

    return ans[MOUSE][2][1];
  }
};
