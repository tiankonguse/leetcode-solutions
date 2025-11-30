
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
class Solution {
 public:
  int countElements(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int ans = 0;
    for (auto v : nums) {
      int idx = upper_bound(nums.begin(), nums.end(), v) - nums.begin();
      if (n - idx >= k) {
        ans++;
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