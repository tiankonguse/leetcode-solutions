
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
  long long maximumTripletValue(vector<int>& nums) {
    int n = nums.size();
    vector<ll> left(n), right(n);
    for (int i = 1; i < n; i++) {
      left[i] = max(left[i - 1], ll(nums[i - 1]));
    }
    for (int i = n - 2; i >= 0; i--) {
      right[i] = max(right[i + 1], ll(nums[i + 1]));
    }
    ll ans = 0;
    for (int i = 1; i + 1 < n; i++) {
      ans = max(ans, (left[i] - nums[i]) * right[i]);
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