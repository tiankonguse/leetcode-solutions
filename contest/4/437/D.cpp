
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
const int N = 510;
int dp[N][N][4][2][2];

int dir4[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int stepVal[2] = {2, 0};
class Solution {
  vector<vector<int>> grid;
  int n, m;
  int Dfs(const int x, const int y, const int d, const int op, const int step) {
    int& ret = dp[x][y][d][op][step];
    if (ret != -1) return ret;

    if (grid[x][y] != stepVal[step]) return ret = 0;

    ret = 1;

    const int X = x + dir4[d][0];
    const int Y = y + dir4[d][1];
    int ans1 = -1;
    if (X >= 0 && X < n && Y >= 0 && Y < m) {
      ans1 = Dfs(X, Y, d, op, 1 - step);
      ret = max(ret, 1 + ans1);
    }

    int ans2 = -1;
    if (op == 0) {  // 转向
      ans2 = Dfs(x, y, (d + 1) % 4, 1, step);
      ret = max(ret, ans2);
    }
    printf("x=%d y=%d d=%d op=%d step=%d ans=%d ans1=%d ans2=%d\n", x, y, d, op, step, ret, ans1, ans2);

    return ret;
  }

 public:
  int lenOfVDiagonal(vector<vector<int>>& grid_) {
    grid.swap(grid_);
    n = grid.size();
    m = grid.front().size();
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] != 1) continue;
        ans = max(ans, 1);
        for (int d = 0; d < 4; d++) {
          const int X = i + dir4[d][0];
          const int Y = j + dir4[d][1];
          if (X >= 0 && X < n && Y >= 0 && Y < m) {
            ans = max(ans, 1 + Dfs(X, Y, d, 0, 0));
          }
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif