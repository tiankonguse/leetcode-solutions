
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
  ll maximumScore(vector<int>& nums) {
    int n = nums.size();
    vector<ll> prefixSum(n + 2, 0);
    for (int i = 1; i <= n; i++) {
      prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
    }
    vector<ll> suffixMin(n + 2, INT64_MAX);
    for (int i = n; i >= 1; i--) {
      suffixMin[i] = min(suffixMin[i + 1], (ll)nums[i - 1]);
    }
    ll ans = INT64_MIN;
    for (int i = 1; i < n; i++) {
      ll sum = prefixSum[i] - suffixMin[i + 1];
      if (sum > ans) ans = sum;
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