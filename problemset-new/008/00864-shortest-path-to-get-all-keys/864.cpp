#include <bits/stdc++.h>

#include "base.h"
using namespace std;

class Solution {
  int k = 0;
  int n, m;
  vector<string> grid;
  vector<int> order;  // k 把钥匙的获取顺序
  vector<int> flag;
  vector<pair<int, int>> keyPos;
  // dp[a][b][key] 有 key 钥匙从 a 到 b 的最短路
  vector<vector<vector<int>>> dp;

  vector<vector<int>> step;
  int stepNum = 0;

  int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  void Bfs(int a, int key) {
    stepNum++;
    queue<tuple<int, int, int>> que;
    auto [x, y] = keyPos[a];
    que.push({x, y, 0});
    step[x][y] = stepNum;
    // printf("x=%d y=%d\n", x, y);

    while (!que.empty()) {
      auto [x, y, num] = que.front();
      que.pop();
      num++;

      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;

        char c = grid[X][Y];
        if (c == '#') continue;
        if (step[X][Y] == stepNum) continue;

        if (c >= 'A' && c <= 'Z') {
          int v = c - 'A';
          if ((key & (1 << v)) == 0) continue;  // 没有钥匙
        }

        if (c >= 'a' && c <= 'z') {
          int v = c - 'a';
          dp[a][v][key] = num;
          //   printf("from=%d to=%d key=%d num=%d X=%d Y=%d\n", a, v, key, num,
          //   X, Y);
        }

        step[X][Y] = stepNum;
        que.push({X, Y, num});
      }
    }
  }

  void Init() {
    int KEY = 1 << k;
    dp.resize(k + 1, vector<vector<int>>(k, vector<int>(KEY, -1)));
    for (int i = 0; i <= k; i++) {
      for (int key = 0; key < KEY; key++) {
        Bfs(i, key);
      }
    }
  }

  int ans = INT_MAX;
  void Check() {
    int key = 0;
    int pre = k;

    int tmp = 0;
    for (auto to : order) {
      // pre -> to
      int d = dp[pre][to][key];
      if (d < 0) return;  // 没有答案
      tmp += d;
      key |= 1 << to;
      pre = to;
    }
    // printf("%d", k);
    // for(int i=0;i<k;i++){
    //     printf("->%d", order[i]);
    // }
    // printf(" tmp=%d\n", tmp);
    ans = min(ans, tmp);
  }

  void DfsA() {
    if (order.size() == k) {
      Check();
      return;
    }

    for (int i = 0; i < k; i++) {
      if (flag[i]) continue;
      order.push_back(i);
      flag[i] = 1;
      DfsA();
      flag[i] = 0;
      order.pop_back();
    }
  }

 public:
  int shortestPathAllKeys(vector<string>& grid_) {
    grid.swap(grid_);
    n = grid.size();
    m = grid.front().size();
    step.resize(n, vector<int>(m, stepNum));

    pair<int, int> start;
    keyPos.resize(26);
    k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char c = grid[i][j];
        if (c == '@') {
          start = {i, j};
        } else if (c >= 'a' && c <= 'z') {
          int v = c - 'a';
          k = max(k, v + 1);
          keyPos[v] = {i, j};
        }
      }
    }
    keyPos.resize(k);
    keyPos.push_back(start);

    order.reserve(k);
    flag.resize(k, 0);
    Init();
    // printf("DfsA k=%d\n", k);
    DfsA();

    if (ans == INT_MAX) {
      ans = -1;
    }
    return ans;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
