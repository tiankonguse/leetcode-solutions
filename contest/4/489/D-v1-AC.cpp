
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
  int maxXor(vector<int>& nums1, int k) {
    vector<int> nums;
    nums.reserve(nums1.size());
    for (auto v : nums1) {
      nums.push_back(v);
      if (nums.size() > 3) {
        int n = nums.size();
        if (nums[n - 1] == nums[n - 2] && nums[n - 2] == nums[n - 3]) {
          nums.pop_back();
        }
      }
    }
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int maxVal = nums[i];
      int minVal = nums[i];
      int xorVal = 0;
      for (int j = i; j < n; j++) {
        maxVal = max(maxVal, nums[j]);
        minVal = min(minVal, nums[j]);
        xorVal ^= nums[j];
        if (maxVal - minVal > k) {
          break;
        }
        ans = max(ans, xorVal);
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