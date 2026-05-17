
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

/*

给你一个 `n x m` 的整数矩阵 `matrix` ，所有元素均为非负整数。

一个 **非零** 单元格 `(row, col)` 会按如下方式检查其附近的单元格：

- 令 `x = matrix[row][col]` 。
- 考虑在 `(row, col)` 的 `x` 行和 `x` 列范围内的每个单元格。
- 忽略矩阵外的单元格。
- 忽略行距离和列距离都恰好等于 `x` 的 单元格。

如果单元格 `(row, col)` 是 **非零** 的，并且所有考虑的单元格中没有一个值 **大于** `x` ，那么该单元格就是一个
**局部最大值** 。

返回一个整数，表示 `matrix` 中 **局部最大值** 的数量。


n 和 m 的范围是 [1, 200] 。
x 的范围是 [0, 200] 。
*/

typedef long long ll;
int dp[201][201][201];  // dp[i][l][r] : i 行 l 列 r 列范围内的最大值
class Solution {
 public:
  int countLocalMaximums(vector<vector<int>>& matrix) {  //
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; i++) {
      for (int l = 0; l < m; l++) {
        for (int r = l; r < m; r++) {
          if (l == r) {
            dp[i][l][r] = matrix[i][l];
          } else {
            dp[i][l][r] = max(dp[i][l][r - 1], matrix[i][r]);
          }
        }
      }
    }
    auto getMax = [&](int row, int col) -> int {
      const int x = matrix[row][col];
      int maxVal = -1;
      for (int i = row - x; i <= row + x; i++) {
        if (i < 0 || i >= n) continue;
        if (i == row - x || i == row + x) {
          int l = max(0, col - matrix[row][col] + 1);
          int r = min(m - 1, col + matrix[row][col] - 1);
          maxVal = max(maxVal, dp[i][l][r]);
        } else {
          int l = max(0, col - matrix[row][col]);
          int r = min(m - 1, col + matrix[row][col]);
          maxVal = max(maxVal, dp[i][l][r]);
        }
      }
      return maxVal;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (matrix[i][j] == 0) continue;
        if (matrix[i][j] == getMax(i, j)) {
          ans++;
        }
      }
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