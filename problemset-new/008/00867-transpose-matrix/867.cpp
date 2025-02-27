
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
  vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    // 得到矩阵的转置矩阵
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        ans[j][i] = matrix[i][j];
      }
    }
    return ans;
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