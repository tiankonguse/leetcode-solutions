
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
  int maxRectangleArea(vector<vector<int>>& points) {
    sort(points.begin(), points.end());
    int ans = -1;
    int n = points.size();
    for (int a = 0; a < n; a++) {
      int ax = points[a][0];
      int ay = points[a][1];
      bool nextAB = false;  // 只能与第一个比较
      bool nextAC = false;
      bool nextCD = false;
      for (int b = a + 1; b < n && !nextAB; b++) {
        int bx = points[b][0];
        int by = points[b][1];
        if (bx > ax) break;
        nextAB = true;
        for (int c = b + 1; c < n && !nextAC; c++) {
          int cx = points[c][0];
          int cy = points[c][1];
          if (cx == ax) continue;
          if (cy > ay && cy <= by) break;  // 再中间
          if (cy != ay) continue;
          nextAC = true;
          for (int d = c + 1; d < n && !nextCD; d++) {
            int dx = points[d][0];
            int dy = points[d][1];
            if (dx > cx) break;
            if (by != dy) break;
            nextCD = true;
            ans = max(ans, (cx - ax) * (dy - ay));
          }
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif