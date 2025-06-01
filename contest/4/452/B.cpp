
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
 public:
  vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
    vector<int> vals;
    vals.reserve(k * k);
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> ans(n - k + 1, vector<int>(m - k + 1, 0));
    if (k == 1) return ans;
    for (int i = 0; i < n - k + 1; i++) {
      for (int j = 0; j < m - k + 1; j++) {
        vals.clear();
        for (int x = i; x < i + k; x++) {
          for (int y = j; y < j + k; y++) {
            vals.push_back(grid[x][y]);
          }
        }
        sort(vals.begin(), vals.end());
        int dis = INT_MAX;
        for (int x = 1; x < k * k; x++) {
          if (vals[x] != vals[x - 1]) {
            dis = min(dis, vals[x] - vals[x - 1]);
          }
        }
        if (dis == INT_MAX) {
          dis = 0;
        }
        ans[i][j] = dis;
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