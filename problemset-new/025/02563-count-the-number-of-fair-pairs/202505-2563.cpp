
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
  long long countFairPairs(vector<int>& nums, int lower, int upper) {
    ll ans = 0;
    int n = nums.size();
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++) {
      int v = nums[i];
      int lowerV = lower - v;
      int upperV = upper - v;
      int l = lower_bound(nums.begin() + i + 1, nums.end(), lowerV) - nums.begin();
      int r = upper_bound(nums.begin() + i + 1, nums.end(), upperV) - nums.begin();
      ans += r - l;
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