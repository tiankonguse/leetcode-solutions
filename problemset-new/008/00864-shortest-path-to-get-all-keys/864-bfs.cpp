#include <bits/stdc++.h>

#include "base.h"
using namespace std;

int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
 public:
  int shortestPathAllKeys(vector<string>& grid) {
    vector<vector<vector<int>>> dp;
    int n = grid.size();
    int m = grid.front().size();
    int k = 0;
    pair<int, int> start;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        char c = grid[i][j];
        if (c == '@') {
          start = {i, j};
        } else if (c >= 'a' && c <= 'z') {
          int v = c - 'a';
          k = max(k, v + 1);
        }
      }
    }

    dp.resize(n, vector<vector<int>>(m, vector<int>(1 << k, -1)));

    auto [x, y] = start;
    queue<tuple<int, int, int>> que;
    que.push({x, y, 0});
    dp[x][y][0] = 0;

    while (!que.empty()) {
      auto [x, y, key] = que.front();
      que.pop();
      int num = dp[x][y][key] + 1;

      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        int KEY = key;
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;

        char c = grid[X][Y];
        if (c == '#') continue;

        if (c >= 'A' && c <= 'Z') {  // 这一步是墙，但是没有钥匙
          int v = c - 'A';
          if ((key & (1 << v)) == 0) continue;  // 没有钥匙
        }

        if (c >= 'a' && c <= 'z') {  // 这一步是钥匙
          int v = c - 'a';
          KEY |= 1 << v;
        }

        if (KEY + 1 == 1 << k) return num;

        if (dp[X][Y][KEY] != -1) continue;  //已经到达过了

        dp[X][Y][KEY] = num;
        que.push({X, Y, KEY});
      }
    }

    return -1;
  }
};

int main() {
  printf("hello ");
  //   vector<double> ans = {1.00000,-1.00000,3.00000,-1.00000};
  //   vector<vector<int>> cars = {{1, 2}, {2, 1}, {4, 3}, {7, 2}};
  //   TEST_SMP1(Solution, getCollisionTimes, ans, cars);

  return 0;
}
