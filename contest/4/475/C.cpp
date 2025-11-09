
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

typedef long long ll;
class Solution {
  vector<vector<vector<int>>> dp;
  int dfs(vector<vector<int>>& grid, int x, int y, int k) {
    if (x < 0 || y < 0 || k < 0) return INT_MIN;
    int& ret = dp[x][y][k];
    if (ret != -1) return ret;
    if (x == 0 && y == 0) {
      return ret = grid[0][0];  // 出口
    }

    // 从上方或左方格子过来
    int cost = 0;
    if (grid[x][y] > 0) {
      cost = 1;
    }
    int up = dfs(grid, x - 1, y, k - cost) + grid[x][y];
    int left = dfs(grid, x, y - 1, k - cost) + grid[x][y];
    return ret = max(up, left);
  }

 public:
  int maxPathScore(vector<vector<int>>& grid, int k) {
    int n = grid.size();
    int m = grid[0].size();
    dp.resize(n, vector<vector<int>>(m, vector<int>(k + 1, -1)));
    int ans = dfs(grid, n - 1, m - 1, k);
    if (ans < 0) {
      ans = -1;
    }
    return ans;
  }
};
#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif