
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
  ll maxAlternatingSum(vector<int>& nums) {
    ll ans = INT64_MIN;
    int n = nums.size();
    vector<ll> preMax(n + 1, INT64_MIN);
    // pre[0][i] = max sum of even index
    // pre[1][i] = max sum of odd index
    ll preSum = 0;
    ll preMin = INT64_MAX;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        preSum += nums[i];
      } else {
        preSum -= nums[i];
      }
      if (i == 0) {
        preMax[i] = preSum;
        preMin = preSum;
      } else {
        preMax[i] = max(preSum, preSum - preMin);
        preMin = min(preMin, preSum);
      }
      ans = max(ans, preMax[i]);
      MyPrintf("preMax[%d] = %lld, ans=%lld\n", i, preMax[i], ans);
    }
    vector<ll> sufMax(n + 1, INT64_MIN);
    ll sufSum = 0;
    ll sufMin = INT64_MAX;
    for (int i = n - 1; i >= 0; i--) {
      if (i % 2 == 1) {
        sufSum += nums[i];
      } else {
        sufSum -= nums[i];
      }
      if (i == n - 1) {
        sufMax[i] = sufSum;
        sufMin = sufSum;
      } else {
        sufMax[i] = max(sufSum, sufSum - sufMin);
        sufMin = min(sufMin, sufSum);
      }
      if (i > 0) {
        ans = max(ans, sufMax[i]);
      }
      MyPrintf("sufMax[%d] = %lld, ans=%lld\n", i, sufMax[i], ans);
    }

    for (int i = 1; i + 1 < n; i++) {
      ll left = preMax[i - 1];
      ll right = sufMax[i + 1];
      ans = max(ans, left + right);
      MyPrintf("left = %lld, right = %lld, tmpAns = %lld, ans = %lld\n", left, right, left + right, ans);
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