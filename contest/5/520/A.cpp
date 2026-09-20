
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
  int countIntersectingIntervals(vector<vector<int>> &intervals) {
    auto Cross = [](const vector<int> &a, const vector<int> &b) -> bool {
      int aL = a[0], aR = a[1];
      int bL = b[0], bR = b[1];
      if (aL > bL) {
        swap(aL, bL);
        swap(aR, bR);
      }
      // 保证 aL <= bL
      return aR >= bL;
    };
    int ans = 0;
    int n = intervals.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (Cross(intervals[i], intervals[j])) {
          ans++;
        }
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