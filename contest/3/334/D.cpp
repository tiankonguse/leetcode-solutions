// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
int dir4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
 public:
  int minimumTime(vector<vector<int>>& grid) {
    if (grid[0][1] != 1 && grid[1][0] != 1) return -1;

    int n = grid.size();
    int m = grid.front().size();
    vector<vector<int>> minTime(n + 1, vector<int>(m + 1, -1));
    min_queue<tuple<int, int, int>> que;
    que.emplace(0, 0, 0);
    minTime[0][0] = 0;

    while (!que.empty()) {
      auto [t, x, y] = que.top();
      que.pop();
      if (x == n - 1 && y == m - 1) return t;

      for (int i = 0; i < 4; i++) {
        int X = x + dir4[i][0];
        int Y = y + dir4[i][1];
        if (X < 0 || X >= n || Y < 0 || Y >= m) continue;

        int T = t + 1;
        if (grid[X][Y] > T) {
          int k = (grid[X][Y] - T + 1) / 2;
          T += k * 2;
        }

        if (minTime[X][Y] == -1 || (minTime[X][Y] != -1 && minTime[X][Y] > T)) {
          minTime[X][Y] = T;
          que.emplace(T, X, Y);
        }
      }
    }
    return -1;
  }
};