
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
  vector<int> searchRange(vector<int>& nums, int target) {
    int n = nums.size();
    int left = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    if (left == n || nums[left] != target) return {-1, -1};
    int right = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
    return {left, right - 1};
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