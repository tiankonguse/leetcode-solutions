
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
  ll minCost(vector<int>& nums) {
    ll n = nums.size();
    ll ans = (n - 1) * nums[1];
    for (ll i = 1; i < n - 1; i++) {
      ll j = i;
      while (j < n && nums[j] == nums[i]) {
        j++;
      }
      j--;
      MyPrintf("i=%lld, j=%lld\n", i, j);
      ll leftCost = (i - 0) * nums[i];
      if (i == 1 && nums[i] == nums[i - 1]) {
        leftCost = 0;
      }
      ll rightCost = (n - 1 - j) * nums[i];
      ll tmpAns = leftCost + rightCost;
      MyPrintf("leftCost=%lld, rightCost=%lld, tmpAns=%lld\n", leftCost, rightCost, tmpAns);
      ans = min(ans, tmpAns);
      i = j;
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