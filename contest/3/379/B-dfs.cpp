// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll m[10][10][10][10];

int dir0[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int dir1[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

class Solution {
  bool OK(int x, int y) { return x >= 1 && x <= 8 && y >= 1 && y <= 8; }
  int x3, y3;

  bool Finish(int x, int y) { return x == x3 && y == y3; }

  ll Dfs(const int x0, const int y0, const int x1, const int y1) {
    auto& ret = m[x0][y0][x1][y1];
    if (ret != -1) return ret;

    if (!OK(x0, y0)) {
      return ret = INT_MAX;
    }
    if (!OK(x1, y1)) {
      return ret = INT_MAX;
    }

    if (Finish(x0, y0)) {
      return ret = 0;
    }

    if (Finish(x1, y1)) {
      return ret = 0;
    }

    ret = INT_MAX;

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        int x = x0 + dir0[i][0] * j;
        int y = y0 + dir0[i][1] * j;
        if (!OK(x, y)) break;
        if (x == x1 && y == y1) break;  // 重复了
        ret = min(ret, 1 + Dfs(x, y, x1, y1));
      }
    }

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 8; j++) {
        int x = x1 + dir1[i][0] * j;
        int y = y1 + dir1[i][1] * j;
        if (!OK(x, y)) break;
        if (x == x0 && y == y0) break;  // 重复了
        ret = min(ret, 1 + Dfs(x0, y0, x, y));
      }
    }

    return ret;
  }

 public:
  int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
    // 最多两步， 最少1步骤
    memset(m, -1, sizeof(m));
    x3 = e, y3 = f;
    return Dfs(a, b, c, d);
  }
};