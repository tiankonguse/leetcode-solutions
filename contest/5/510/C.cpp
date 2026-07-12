
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
  void Path(vector<string>& ans, int x0, int y0) {
    int m = ans.size();
    int n = ans[0].size();

    for (int i = x0; i < m; i++) {
      ans[i][y0] = '.';
    }
    for (int j = y0; j < n; j++) {
      ans[m - 1][j] = '.';
    }
  }
  void Square(vector<string>& ans, int x0, int y0) {
    for (int i = x0; i < x0 + 2; i++) {
      for (int j = y0; j < y0 + 2; j++) {
        ans[i][j] = '.';
      }
    }
  }

 public:
  vector<string> createGrid(int m, int n, int k) {
    vector<string> ans(m, string(n, '#'));
    if (k == 1) {  // L 型
      Path(ans, 0, 0);
      return ans;
    }
    if (n == 1 || m == 1) return {};
    if (k == 2) {
      Square(ans, 0, 0);
      Path(ans, 1, 1);
      return ans;
    }
    if (n == 2 && m == 2) return {};
    if (k == 3) {
      if (m >= 2 && n >= 3) {
        Square(ans, 0, 0);
        Square(ans, 0, 1);
        Path(ans, 1, 2);
        return ans;
      } else if (m >= 3 && n >= 2) {
        Square(ans, 0, 0);
        Square(ans, 1, 0);
        Path(ans, 2, 1);
        return ans;
      } else {
        return {};
      }
    } else if (k == 4) {
      if (m >= 3 && n >= 3) {
        Square(ans, 0, 0);
        Square(ans, 1, 1);
        Path(ans, 2, 2);
        return ans;
      } else if (m >= 2 && n >= 4) {
        Square(ans, 0, 0);
        Square(ans, 0, 1);
        Square(ans, 0, 2);
        Path(ans, 1, 3);
        return ans;
      } else if (m >= 4 && n >= 2) {
        Square(ans, 0, 0);
        Square(ans, 1, 0);
        Square(ans, 2, 0);
        Path(ans, 3, 1);
        return ans;
      }
    }
    return {};
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