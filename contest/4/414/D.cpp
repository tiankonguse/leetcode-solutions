// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

const int A = 0;
const int B = 1;
const int defalutVal[2] = {0, INT_MAX};
typedef long long ll;
const int kMaxN = 50;
const int dir8[8][2] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2},
                        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
class Solution {
  vector<vector<int>> minSteps;
  vector<vector<int>> dp[2];
  void Init() {
    minSteps.resize(n, vector<int>(n, -1));
    vector<vector<int>> grid(kMaxN, vector<int>(kMaxN, -1));
    for (int i = 0; i < n; i++) {
      grid.clear();
      grid.resize(kMaxN, vector<int>(kMaxN, -1));
      for (int j = 0; j < n; j++) {
        const auto& p = positions[j];
        grid[p[0]][p[1]] = -2 - j;  // 标记是特殊位置
      }

      queue<pair<int, int>> que;

      const auto& p = positions[i];
      grid[p[0]][p[1]] = 0;
      que.push({p[0], p[1]});

      while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int k = 0; k < 8; k++) {
          int X = x + dir8[k][0];
          int Y = y + dir8[k][1];
          if (X < 0 || Y < 0 || X >= kMaxN || Y >= kMaxN) continue;
          if (grid[X][Y] >= 0) continue;
          if (grid[X][Y] < -1) {
            int j = -2 - grid[X][Y];
            minSteps[i][j] = grid[x][y] + 1;
          }
          grid[X][Y] = grid[x][y] + 1;
          que.push({X, Y});
        }
      }
    }
  }
  vector<vector<int>> positions;
  int N;
  int n;

  int Dis(int a, int b) { return minSteps[a][b]; }

  int Dfs(int p, int mask, int role) {
    int& ret = dp[role][p][mask];
    if (ret != -1) {
      return ret;
    }
    if (mask == 0) {
      return ret = 0;
    }

    ret = defalutVal[role];
    for (int i = 0; i < N; i++) {
      int M = 1 << i;
      if (mask & M) {
        // 选择 p->i
        int cost = Dis(p, i) + Dfs(i, mask ^ M, 1 - role);
        // myprintf("role=%d p=%d->%d mask=%d cost=%d, dis=%d, nextrole=%d\n",
        //          role, p, i, mask, cost, Dis(p, i), Dfs(i, mask ^ M, 1 - role));
        if (role == A) {
          ret = max(ret, cost);
        } else {
          ret = min(ret, cost);
        }
      }
    }

    // printf("role=%d p=%d mask=%d ans=%d\n", role, p, mask, ret);
    return ret;
  }

 public:
  int maxMoves(int kx, int ky, vector<vector<int>>& positions_) {
    positions.swap(positions_);
    vector<int> start = {kx, ky};
    N = positions.size();
    positions.push_back(start);
    n = positions.size();
    Init();

    dp[A].resize(n, vector<int>(1 << N, -1));
    dp[B].resize(n, vector<int>(1 << N, -1));

    return Dfs(n - 1, (1 << N) - 1, A);
  }
};