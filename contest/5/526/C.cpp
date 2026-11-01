
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
  int minSwapOrder(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (nums[i] > nums[j]) {
          ans++;
        }
      }
    }
    return ans;
  }

 public:
  int minOperations(vector<int>& nums, vector<int>& locked, int k) {
    int n = nums.size();
    vector<int> leftMax(n, nums.front());
    vector<int> rightMin(n, nums.back());
    for (int i = 1; i < n; i++) {
      leftMax[i] = max(leftMax[i - 1], nums[i]);
    }
    for (int i = n - 2; i >= 0; i--) {
      rightMin[i] = min(rightMin[i + 1], nums[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      const int val = i + 1;
      if (locked[i] == 0) continue;
      if (nums[i] != val || leftMax[i] > val || val > rightMin[i]) {
        ans++;
        if (ans > k) return -1;
      }
    }
    ans += minSwapOrder(nums);
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