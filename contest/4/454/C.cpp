
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
    if (n == 1) {
      return nums[0];
    }
    ll ans = ll(nums[0]) * ll(nums[k - 1]);
    set<ll> pre_1, pre_0, pre1;
    for (int i = 0; i < n; i++) {
      int l = i - k + 1;
      if (l < 0) {  // 不够 k 个，跳过
        continue;
      }
      ll rightVal = nums[i];  // 右指针
      ll leftVal = nums[l];   // 左指针

      if (leftVal < 0) {
        pre_1.insert(leftVal);
      } else if (leftVal == 0) {
        pre_0.insert(leftVal);
      } else {
        pre1.insert(leftVal);
      }
      if (!pre_1.empty()) {
        ans = max(ans, *pre_1.begin() * rightVal);
        ans = max(ans, *pre_1.rbegin() * rightVal);
      }
      if (!pre_0.empty()) {
        ans = max(ans, *pre_0.begin() * rightVal);
        ans = max(ans, *pre_0.rbegin() * rightVal);
      }
      if (!pre1.empty()) {
        ans = max(ans, *pre1.begin() * rightVal);
        ans = max(ans, *pre1.rbegin() * rightVal);
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