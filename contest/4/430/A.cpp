
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
  int minimumOperations(vector<vector<int>>& g) {
    int ans = 0;
    int n = g.size();
    int m = g.front().size();
    for (int j = 0; j < m; j++) {
      for (int i = 1; i < n; i++) {
        if (g[i][j] <= g[i - 1][j]) {
          ans += g[i - 1][j] + 1 - g[i][j];
          g[i][j] = g[i - 1][j] + 1;
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