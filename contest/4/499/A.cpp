
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
  vector<int> findValidElements(vector<int>& nums) {
    int n = nums.size();
    if (n <= 2) return nums;
    vector<int> leftMax(n), rightMax(n);
    leftMax[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      leftMax[i] = max(leftMax[i - 1], nums[i]);
    }
    rightMax[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      rightMax[i] = max(rightMax[i + 1], nums[i]);
    }
    vector<int> ans;
    ans.push_back(nums[0]);
    for (int i = 1; i < n - 1; ++i) {
      if (nums[i] > leftMax[i - 1] || nums[i] > rightMax[i + 1]) {
        ans.push_back(nums[i]);
      }
    }
    ans.push_back(nums[n - 1]);

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