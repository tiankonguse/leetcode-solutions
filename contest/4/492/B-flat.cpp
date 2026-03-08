
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
  int smallestBalancedIndex(vector<int>& nums) {
    int n = nums.size();
    vector<ll> pre(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1] + nums[i - 1];
    }
    ll rightMul = 1;
    ll ans = n;
    for (int i = n; i >= 1; i--) {
      if (pre[i - 1] < rightMul) {
        break;
      }
      if (pre[i - 1] == rightMul) {
        ans = i - 1;
      }
      if (i > 1) {
        if (double(rightMul) * nums[i - 1] > pre[i - 2]) {
          break;
        }
        rightMul *= nums[i - 1];
      }
    }
    if (ans == n) {
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