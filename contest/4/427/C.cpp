
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  long long maxSubarraySum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> preSum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      preSum[i] = preSum[i - 1] + nums[i - 1];
    }

    ll ans = preSum[k];
    auto Update = [&ans](ll v) { ans = max(ans, v); };
    for (int i = 1; i <= k; i++) {
      ll pre = 0;
      for (int j = i; j <= n; j += k) {
        int l = j;
        int r = j + k - 1;
        if (r <= n) {
          ll now = preSum[r] - preSum[l - 1];
          Update(now);
          pre += now;
          Update(pre);
          if (pre < 0) {
            pre = 0;
          }
        }
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif©leetcode