
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
  int minRemovals(vector<int>& nums, int target) {
    const int MAXX = 1 << 14;
    const int INF = -1e9;

    vector<int> dp(MAXX, INF);
    dp[0] = 0;

    for (int num : nums) {
      vector<int> tmpDp = dp;
      for (int x = 0; x < MAXX; x++) {
        if (dp[x] == INF) continue;
        tmpDp[x ^ num] = max(tmpDp[x ^ num], dp[x] + 1);
      }
      dp.swap(tmpDp);
    }

    if (dp[target] < 0) return -1;
    return nums.size() - dp[target];
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