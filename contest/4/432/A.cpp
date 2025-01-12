
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
  vector<int> zigzagTraversal(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> ans;
    ans.reserve(n * m);
    int index = 0;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        for (int j = 0; j < m; j++) {
          int v = grid[i][j];
          if (index % 2 == 0) {
            ans.push_back(v);
          }
          index++;
        }
      } else {
        for (int j = m - 1; j >= 0; j--) {
          int v = grid[i][j];
          if (index % 2 == 0) {
            ans.push_back(v);
          }
          index++;
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