
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
  vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    vector<int> prefix(n, 0);  // nums[i-1] 到 nums[i] 的 cost
    prefix[1] = 1;
    for (int i = 2; i < n; i++) {
      int leftCost = abs(nums[i - 2] - nums[i - 1]);
      int rightCost = abs(nums[i - 1] - nums[i]);
      if (leftCost <= rightCost) {
        prefix[i] = prefix[i - 1] + rightCost;
      } else {
        prefix[i] = prefix[i - 1] + 1;
      }
    }
    vector<int> suffix(n, 0);  // nums[i+1] 到 nums[i] 的 cost
    suffix[n - 2] = 1;
    for (int i = n - 3; i >= 0; i--) {
      int leftCost = abs(nums[i] - nums[i + 1]);
      int rightCost = abs(nums[i + 1] - nums[i + 2]);
      if (leftCost <= rightCost) {
        suffix[i] = suffix[i + 1] + 1;
      } else {
        suffix[i] = suffix[i + 1] + leftCost;
      }
    }

    vector<int> ans;
    ans.reserve(queries.size());
    for (const auto& q : queries) {
      int l = q[0], r = q[1];
      if (l <= r) {
        ans.push_back(prefix[r] - prefix[l]);
      } else {
        swap(l, r);
        ans.push_back(suffix[l] - suffix[r]);
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