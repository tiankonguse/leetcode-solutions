
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
  long long maxAlternatingSum(vector<int>& nums) {
    ll ans = 0;
    int n = nums.size();
    vector<ll> nums2;
    nums2.reserve(n);
    for (ll v : nums) {
      nums2.push_back(v * v);
    }
    sort(nums2.begin(), nums2.end());
    int l = 0, r = n - 1;
    while (l <= r) {
      ans += nums2[r--];
      if (l <= r) {
        ans -= nums2[l++];
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