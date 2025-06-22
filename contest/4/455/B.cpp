
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
  vector<int> findCoins(vector<int>& numWays) {
    int n = numWays.size();
    const int W = 101;
    vector<int> dp(101, 0);  // dp[i] i 之前的有效硬币可以组成价值为 i 的方案数
    dp[0] = 1;
    auto Update = [&dp, &W](const int v) {
      for (int l = v; l < W; l++) {
        dp[l] = dp[l] + dp[l - v];
      }
    };
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      // 计算 dp[i]
      int v = numWays[i - 1];
      if (v < dp[i]) {
        MyPrintf("v<dp: i = %d, v = %d, dp[i] = %d\n", i, v, dp[i]);
        return {};
      }
      if (v == dp[i]) {
        MyPrintf("v==dp: i = %d, v = %d, dp[i] = %d\n", i, v, dp[i]);
        continue;
      }
      if (v > dp[i] + 1) {
        MyPrintf("v>dp+1: i = %d, v = %d, dp[i] = %d\n", i, v, dp[i]);
        return {};
      }

      MyPrintf("v==dp+1: i = %d, v = %d, dp[i] = %d\n", i, v, dp[i]);
      Update(i);
      MyPrintf("after v==dp+1: i = %d, v = %d, dp[i] = %d\n", i, v, dp[i]);
      ans.push_back(i);
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