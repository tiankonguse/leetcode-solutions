
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
  int firstStableIndex(vector<int>& nums, int k) {
    int n = nums.size();
    vector<ll> preMax(n, 0), sufMin(n, 0);
    preMax[0] = nums[0];
    for (int i = 1; i < n; i++) {
      preMax[i] = max(preMax[i - 1], (ll)nums[i]);
    }
    sufMin[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      sufMin[i] = min(sufMin[i + 1], (ll)nums[i]);
    }
    int ans = -1;
    for (int i = 0; i < n; i++) {
      if (preMax[i] - sufMin[i] <= k) {
        ans = i;
        break;
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