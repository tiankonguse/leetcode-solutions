
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
  ll minArraySum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> kIndex(k, -1);        //
    vector<int> leftLast(n + 1, -1);  // sum[leftLast[i], i] %k == 0
    ll pre = 0;
    kIndex[0] = 0;
    for (int i = 1; i <= n; i++) {
      ll v = nums[i - 1];
      pre = (pre + v) % k;
      if (kIndex[pre] != -1) {
        leftLast[i] = kIndex[pre] + 1;
      }
      kIndex[pre] = i;
    }

    vector<ll> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      dp[i] = dp[i - 1] + nums[i - 1];
      if (leftLast[i] != -1) {
        dp[i] = min(dp[i], dp[leftLast[i] - 1]);
      }
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