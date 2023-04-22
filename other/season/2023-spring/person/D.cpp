// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
  vector<string> maze;
  int n;
  pair<int, int> S, T;
  vector<vector<int>> TDis;
  vector<vector<int>> AliceFlag;

  void Init() {
    n = maze.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char c = maze[i][j];
        if (c == 'S') {
          S = {i, j};
        } else if (c == 'T') {
          T = {i, j};
        }
      }
    }
    TDis.resize(n, vector<int>(n, -1));
    AliceFlag.resize(n, vector<int>(n, INT_MAX));
  }
  void DfsT() {
    queue<pair<int, int>> que;
    int x = T.first, y = T.second;
    que.push({x, y});
    TDis[x][y] = 0;

    while (!que.empty()) {
      auto [x, y] = que.front();
      que.pop();
      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
        if (maze[X][Y] == '#') continue;
        if (TDis[X][Y] != -1) continue;
        TDis[X][Y] = TDis[x][y] + 1;
        que.push({X, Y});
      }
    }
  }

  int CalBob(int i, int j) {
    int ans = INT_MAX;  // 无法干预

    // 水平干预
    int x0 = n - 1 - i, y0 = j;
    if (maze[x0][y0] != '#') {
      int tmp = TDis[x0][y0];
      if (tmp == -1 || ans == -1) {
        ans = -1;
      } else if (ans == INT_MAX) {
        ans = tmp;
      } else {
        ans = max(ans, tmp);
      }
    }

    // 垂直干预
    int x1 = i, y1 = n - 1 - j;
    if (maze[x1][y1] != '#') {
      int tmp = TDis[x1][y1];
      if (tmp == -1 || ans == -1) {
        ans = -1;
      } else if (ans == INT_MAX) {
        ans = tmp;
      } else {
        ans = max(ans, tmp);
      }
    }
    printf("i=%d j=%d ans=%d\n", i, j, ans);
    return ans;
  }

  // x,y 保证合法
  int Bob(int x, int y) {
    if (x == T.first && y == T.second) {
      return Alice(x, y);
    }
    if (x == S.first && y == S.second) {
      return Alice(x, y);
    }
    // 干预
    int ans1 = CalBob(x, y);
    if (ans1 == -1) return -1;

    // 不干预
    int ans = Alice(x, y);
    if (ans == -1) return -1;

    if (ans1 == INT_MAX) {  // 不可干预，都是石头
      return ans;
    }

    return max(ans, ans1);
  }

  int Alice(int x, int y) {
    if (AliceFlag[x][y] != INT_MAX) {
      return AliceFlag[x][y];
    }
    int& ans = AliceFlag[x][y];

    // 剪枝优化，明确不可到达了
    if (TDis[x][y] == -1) {
      return ans = -1;
    }
    if (x == T.first && y == T.second) {
      return ans = 0;
    }

    ans = -1;  // 防止形成环

    int tmpAns = -1;
    for (int i = 0; i < 4; i++) {
      int X = x + dir4[i][0];
      int Y = y + dir4[i][1];
      if (X < 0 || X >= n || Y < 0 || Y >= n) continue;
      if (maze[X][Y] == '#') continue;

      int tmp = Bob(X, Y);
      if (tmpAns == -1) {
        tmpAns = tmp;
      } else if (tmp != -1) {
        tmpAns = min(tmp, tmpAns);
      }
    }
    printf("alice (%d,%d)=%d\n", x, y, ans);
    return ans = tmpAns;
  }

 public:
  int challengeOfTheKeeper(vector<string>& maze_) {
    maze.swap(maze_);
    Init();
    DfsT();

    if (TDis[S.first][S.second] == -1) {
      return -1;
    }
    return Alice(S.first, S.second);
  }
};