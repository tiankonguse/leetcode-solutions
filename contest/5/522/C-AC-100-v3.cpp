
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
  ll maxAlternatingSum(vector<int>& nums) {
    ll ans = INT64_MIN / 2;
    int n = nums.size();
    ll flag[2] = {1, -1};
    vector<vector<ll>> preRangeMax(2, vector<ll>(n + 1, INT64_MIN / 2));
    // pre[0][i] = 下标 i 作为偶数下标结尾的最大后缀和(包含下标 i)
    // pre[1][i] = 下标 i 作为奇数下标的最大后缀和(包含下标 i)
    ll preSum = 0;
    ll preMin[2] = {0, 0};
    ll preMax[2] = {0, 0};
    // preMin[0] 偶数下标为后缀的的位置中的最小前缀和
    // preMin[1] 奇数下标为后缀的的位置中的最小前缀和
    for (int i = 0; i < n; i++) {
      MyPrintf("i=%d\n", i);
      ll v = nums[i];
      int o = i % 2;
      preSum += flag[o] * v;
      if (i == 0) {
        preRangeMax[0][i] = preSum;
        preMin[o] = preSum;
        preMax[o] = preSum;
      } else {
        preRangeMax[o][i] = preSum - preMin[1];
        preRangeMax[1 - o][i] = (-preSum) + preMax[0];
        preMin[o] = min(preMin[o], preSum);
        preMax[o] = max(preMax[o], preSum);
      }
      MyPrintf("preRangeMax[0][%d] = %lld preRangeMax[1][%d] = %lld, preMin[0] = %lld, preMin[1] = %lld\n", i,
               preRangeMax[0][i], i, preRangeMax[1][i], preMin[0], preMin[1]);
      ans = max(ans, preRangeMax[0][i]);
      ans = max(ans, preRangeMax[1][i]);
    }
    // 0 1 0 1 0 1
    vector<vector<ll>> sufRangeMax(2, vector<ll>(n + 2, INT64_MIN / 2));
    ll sufSum = 0;
    ll sufMin = 0;
    ll sufMax = 0;
    // sufMin 默认符号的最小后缀和
    // sufMax 反转符号的最小后缀和
    for (int i = n - 1; i >= 0; i--) {
      MyPrintf("i=%d\n", i);
      ll v = nums[i];
      int o = i % 2;
      sufSum += flag[o] * v;

      sufRangeMax[o][i] = sufSum - sufMin;
      sufRangeMax[1 - o][i] = (-sufSum) + sufMax;
      sufMin = min(sufMin, sufSum);
      sufMax = max(sufMax, sufSum);

      if (i > 0) {
        MyPrintf("sufRangeMax[0][%d] = %lld\n", i, sufRangeMax[0][i]);
        ans = max(ans, sufRangeMax[0][i]);
      }

      MyPrintf("sufRangeMax[0][%d] = %lld sufRangeMax[1][%d] = %lld, sufMin = %lld, sufMax = %lld\n", i,
               sufRangeMax[0][i], i, sufRangeMax[1][i], sufMin, sufMax);
    }

    for (int i = 1; i + 1 < n; i++) {
      for (int li = 0; li < 2; li++) {
        ll left = preRangeMax[li][i - 1];
        ll right = sufRangeMax[1 - li][i + 1];
        ans = max(ans, left + right);
        MyPrintf("i=%d li=%d left = %lld, right = %lld, tmpAns = %lld, ans = %lld\n", i, li, left, right, left + right,
                 ans);
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