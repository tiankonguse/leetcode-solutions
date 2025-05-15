
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
  bool canPartitionGrid(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<ll> row(n, 0);
    vector<ll> col(m, 0);
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        row[i] += grid[i][j];
        col[j] += grid[i][j];
        sum += grid[i][j];
      }
    }
    if (sum % 2 != 0) return false;
    sum /= 2;
    ll tmp = 0;
    for (int i = 0; i < n; ++i) {
      tmp += row[i];
      if (tmp == sum) return true;
    }
    tmp = 0;
    for (int j = 0; j < m; ++j) {
      tmp += col[j];
      if (col[j] == sum) return true;
    }
    return false;
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