
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
  vector<vector<int>> ans;

 public:
  vector<vector<int>> specialGrid(int n) {  //
    int N = 1 << n;
    ans = vector<vector<int>>(N, vector<int>(N, 0));
    int offset = 0;
    Dfs(0, 0, N, offset);
    return ans;
  }

  void Dfs(int x, int y, int N, int& offset) {
    if (N == 1) {
      ans[x][y] = offset;
      offset++;
      return;
    }
    // 右上，右下，左下，左上
    int n = N / 2;
    Dfs(x, y + n, n, offset);
    Dfs(x + n, y + n, n, offset);
    Dfs(x + n, y, n, offset);
    Dfs(x, y, n, offset);
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