
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
  int countConsistent(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    for (int l = 0; l < n; l++) {
      int val = nums[l];
      int minVal = nums[l];
      for (int r = l; r < n; r++) {
        minVal = min(minVal, nums[r]);
        val = val & nums[r];
        if (val == minVal) {
          ans++;
        }
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