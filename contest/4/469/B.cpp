
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
  long long splitArray(vector<int>& nums) {
    int n = nums.size();
    vector<ll> preSum(n + 2, 0);
    vector<ll> suffSum(n + 2, 0);
    vector<bool> preOK(n + 2, 0), suffOK(n + 2, 0);
    preOK[1] = 1;
    for (int i = 1; i <= n; i++) {
      preSum[i] = preSum[i - 1] + nums[i - 1];
      if (i > 1 && preOK[i - 1] && nums[i - 1] > nums[i - 2]) {
        preOK[i] = 1;
      }
    }
    suffOK[n] = 1;
    for (int i = n; i >= 1; i--) {
      suffSum[i] = suffSum[i + 1] + nums[i - 1];
      if (i < n && suffOK[i + 1] && nums[i - 1] > nums[i]) {
        suffOK[i] = 1;
      }
    }

    ll sum = accumulate(nums.begin(), nums.end(), 0LL);
    ll ans = sum;
    for (int i = 1; i < n; i++) {
      if (preOK[i] && suffOK[i + 1]) {
        ans = min(ans, abs(preSum[i] - suffSum[i + 1]));
      }
    }
    if (ans == sum) {
      ans = -1;
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