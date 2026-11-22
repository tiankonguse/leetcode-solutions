
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
  ll minCost(vector<int>& nums) {
    int n = nums.size();
    if (n == 2 || n == 3) {
      return ll(nums.front()) + ll(nums.back());
    }
    ll preCost = ll(nums[0]) + ll(nums[1]) + ll(nums[2]);
    ll nextCost = ll(nums[0]) + ll(nums[2]) + ll(nums[3]);
    nextCost = min(nextCost, preCost);

    ll ans = 0;
    for (int i = 3; i < n; i++) {
      ll cost1 = ll(nums.front()) + nums[i];
      ll cost2 = preCost + nums[i];
      if (i + 1 == n) {
        ans = min(cost1, cost2);
        break;
      }
      preCost = nextCost;
      nextCost = min(nextCost, min(cost1, cost2) + nums[i + 1]);
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