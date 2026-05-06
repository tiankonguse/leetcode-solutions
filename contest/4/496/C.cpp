
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
  long long minIncrease(vector<int>& nums) {
    int n = nums.size();
    auto V = [&](int i) { return nums[i - 1]; };
    vector<ll> dp(n + 2, 0);  // dp[i] 前 i 个数形成 (i-1)/2 个特殊下标时的最小操作数
    dp[0] = dp[1] = dp[2] = 0;
    for (int i = 3; i <= n; i++) {
      ll ab = max(V(i), V(i - 2));
      ll tmp = 0;
      if (V(i - 1) <= ab) {
        tmp = ab - V(i - 1) + 1;
      }
      if (i % 2 == 1) {  // 奇数，必须全部形成特殊下标
        dp[i] = dp[i - 2] + tmp;
      } else {  // 偶数，允许浪费一个
        dp[i] = min(dp[i - 1], dp[i - 2] + tmp);
      }
      MyPrintf("dp[%d] = %lld\n", i, dp[i]);
    }

    return dp[n];
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