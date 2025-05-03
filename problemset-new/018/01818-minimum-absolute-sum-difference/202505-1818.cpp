
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
const ll mod = 1e9 + 7;
class Solution {
 public:
  int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
    ll ans = 0;
    int n = nums1.size();
    for (int i = 0; i < n; i++) {
      ans = ans + abs(nums1[i] - nums2[i]);
    }

    vector<int> nums = nums1;
    sort(nums.begin(), nums.end());
    const ll base = ans;
    for (int i = 0; i < n; i++) {
      ll v = nums2[i];
      ll dis = abs(nums1[i] - nums2[i]);

      auto it = lower_bound(nums.begin(), nums.end(), v);
      if (it != nums.end()) {
        dis = min(dis, abs(*it - v));
      }
      if (it != nums.begin()) {
        --it;
        dis = min(dis, abs(*it - v));
      }
      ans = min(ans, base - abs(nums1[i] - nums2[i]) + dis);
    }
    return ans % mod;
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