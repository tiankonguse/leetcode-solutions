
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
class Solution {
 public:
  vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<int> buf(n);
    // 左下角
    int X = n - 1, Y = 0;
    for (int col = 0; col < n; col++) {  // 列数
      buf.clear();
      for (int x = X, y = Y; x < n && y < n; x++, y++) {
        buf.push_back(grid[x][y]);
      }
      sort(buf.begin(), buf.end());
      for (int x = X, y = Y; x < n && y < n; x++, y++) {
        grid[x][y] = buf.back();
        buf.pop_back();
      }
      X--;
    }

    X = n - 2, Y = n - 1;
    for (int col = n - 2; col > 0; col--) {
      buf.clear();
      for (int x = X, y = Y; x >= 0 && y >= 0; x--, y--) {
        buf.push_back(grid[x][y]);
      }
      sort(buf.begin(), buf.end());
      for (int x = X, y = Y; x >= 0 && y >= 0; x--, y--) {
        grid[x][y] = buf.back();
        buf.pop_back();
      }
      X--;
    }

    return grid;
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