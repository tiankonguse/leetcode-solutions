
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
  vector<vector<int>> findDisappearedNumbers(vector<int>& nums, int lower, int upper) {
    int n = nums.size();
    nums.push_back(lower - 1);
    nums.push_back(upper + 1);
    sort(nums.begin(), nums.end());
    vector<vector<int>> ret;
    ret.reserve(nums.size() + 1);

    auto l = lower_bound(nums.begin(), nums.end(), lower) - nums.begin();
    auto r = lower_bound(nums.begin(), nums.end(), upper) - nums.begin();
    for (auto i = l; i <= r; i++) {
      if (nums[i] - nums[i - 1] > 1) {
        ret.push_back({nums[i - 1] + 1, nums[i] - 1});
      }
    }
    return ret;
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