
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int minMoves(ll sx, ll sy, ll tx, ll ty) {
    // (x, y) -> (x, 2y) | (x+y, y)
    int ans = 0;
    bool eqFlag = false;
    while (1) {
      MyPrintf("begin tx = %lld, ty = %lld, sx=%lld sy=%lld ans = %d\n", tx, ty, sx, sy, ans);
      if (tx == sx && sy == ty) return ans;
      if (eqFlag && tx == sy && ty == sx) return ans;
      if (tx == ty) eqFlag = true;
      if (tx < ty) {
        swap(tx, ty);
        swap(sx, sy);
        MyPrintf("swap\n");
        MyPrintf("tx = %lld, ty = %lld, sx=%lld sy=%lld ans = %d\n", tx, ty, sx, sy, ans);
      }
      if (tx >= ty * 2) {
        if (tx % 2 == 1) return -1;
        tx /= 2;
      } else {
        tx -= ty;
      }
      ans++;
      MyPrintf("end tx = %lld, ty = %lld, sx=%lld sy=%lld ans = %d\n", tx, ty, sx, sy, ans);
    }
    return -1;
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