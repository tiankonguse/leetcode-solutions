
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
    sort(nums.begin(), nums.end());
    vector<vector<int>> ret;
    ret.reserve(nums.size() + 1);

    int n = nums.size();
    int i = 0;
    while (lower <= upper) {
      while (i < n && nums[i] < lower) i++;
      if (i == n || nums[i] > upper) {
        ret.push_back({lower, upper});
        break;
      } else {
        const int val = nums[i];
        if (val != lower) {
          ret.push_back({lower, val - 1});
        }
        lower = val + 1;
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