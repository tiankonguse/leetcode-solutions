
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
  ll MinValue(vector<int>& nums, int offset) {
    int n = nums.size();
    ll minVal = 0;
    ll preSum = 0;
    ll flag = offset == 0 ? 1 : -1;
    for (int i = offset; i + 1 < n; i += 2) {
      ll v1 = nums[i] * flag;
      ll v2 = nums[i + 1] * (-flag);

      preSum += v1 + v2;
      minVal = min(minVal, preSum);
      if (preSum > 0) {
        preSum = 0;
      }
    }
    return minVal;
  }

 public:
  ll maxValue(vector<int>& nums) {
    ll sum = 0;
    int flag = 1;
    for (ll v : nums) {
      v *= flag;
      flag = -flag;
      sum += v;
    }
    ll minVal = min(MinValue(nums, 0), MinValue(nums, 1));
    return sum - minVal * 2;
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