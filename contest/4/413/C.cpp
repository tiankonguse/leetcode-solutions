// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  vector<int> maxLeft;
  vector<vector<int>> grid;
  vector<int> flag;
  int ans = 0;
  int n;

  void Dfs(int i, const int sum) {
    ans = max(ans, sum);
    if (i >= n) return;
    // 剪枝
    if (sum + maxLeft[i] <= ans) return;  // 选择最大的也不会更优

    for (auto v : grid[i]) {
      if (flag[v]) continue;
      // 选择 v
      flag[v] = 1;
      Dfs(i + 1, sum + v);
      // 不选择 v
      flag[v] = 0;
    }
    Dfs(i + 1, sum);  // 这一行都不选
  }

 public:
  int maxScore(vector<vector<int>>& grid_) {
    grid.swap(grid_);
    n = grid.size();
    for (auto& g : grid) {
      set<int> s = {g.begin(), g.end()};
      g = {s.rbegin(), s.rend()};
      for (auto v : g) {
        myprintf("%d ", v);
      }
      printf("\n");
    }
    maxLeft.resize(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
      maxLeft[i] = maxLeft[i + 1] + grid[i].front();
    }
    myprintf("dfs\n", "");
    flag.resize(111, 0);
    Dfs(0, 0);

    return ans;
  }
};