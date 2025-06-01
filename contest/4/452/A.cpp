
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
  vector<int> nums;
  ll target;
  int n;
  bool dfs(ll A, ll B, int p) {
    if (p == n) {
      return A == B && A == target;
    }
    // A 选择
    if (A * nums[p] <= target) {
      if (dfs(A * nums[p], B, p + 1)) {
        return true;
      }
    }
    if (B * nums[p] <= target) {
      if (dfs(A, B * nums[p], p + 1)) {
        return true;
      }
    }
    return false;
  }

 public:
  bool checkEqualPartitions(vector<int>& nums_, ll target_) {
    target = target_;
    nums.swap(nums_);
    n = nums.size();
    return dfs(1, 1, 0);
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