
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
  ll maximumProduct(vector<int>& nums, int k) {
    int n = nums.size();
    ll ans = ll(nums[0]) * ll(nums[k - 1]);
    ll leftMin = 0, leftMax = *min_element(nums.begin(), nums.end()) - 1, haveLeft = 0;
    ll rightMin = *max_element(nums.begin(), nums.end()) + 1, rightMax = 0, haveRight = 0;
    ll mid = 0, haveMid = 0;
    for (int i = 0; i < n; i++) {
      int l = i - k + 1;
      if (l < 0) {  // 不够 k 个，跳过
        continue;
      }
      ll rightVal = nums[i];  // 右指针
      ll leftVal = nums[l];   // 左指针

      if (leftVal < 0) {
        haveLeft = 1;
        leftMin = min(leftMin, leftVal);
        leftMax = max(leftMax, leftVal);
      } else if (leftVal == 0) {
        haveMid = 1;
        mid++;
      } else {
        haveRight = 1;
        rightMin = min(rightMin, leftVal);
        rightMax = max(rightMax, leftVal);
      }
      if (haveLeft) {
        ans = max(ans, leftMin * rightVal);
        ans = max(ans, leftMax * rightVal);
      }
      if (haveMid) {
        ans = max(ans, 0 * rightVal);
      }
      if (haveRight) {
        ans = max(ans, rightMin * rightVal);
        ans = max(ans, rightMax * rightVal);
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