
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
  vector<vector<int>> grid;
  vector<vector<int>> valid;  // 是否有效
  int limit;
  int row, col;
  void Init() {
    valid.resize(col, vector<int>(col, 0));
    for (int l = 0; l < col; l++) {
      for (int r = l + 1; r < col; r++) {
        int flag = 1;
        for (int i = 0; i < row; i++) {
          if (abs(grid[i][r] - grid[i][l]) > limit) {
            flag = 0;
            break;
          }
        }
        valid[l][r] = flag;
      }
    }
  }

 public:
  int maxConsistentColumns(vector<vector<int>>& grid_, const int limit) {  //
    this->limit = limit;
    grid.swap(grid_);
    row = grid.size();
    col = grid[0].size();
    Init();
    vector<int> dp(col, 1);
    int ans = 1;
    for (int i = 0; i < col; i++) {
      for (int j = 0; j < i; j++) {
        if (valid[j][i]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
      ans = max(ans, dp[i]);
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