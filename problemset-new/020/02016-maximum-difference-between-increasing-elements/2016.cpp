
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
  int maximumDifference(vector<int>& nums) {
    int ans = -1;
    int maxVal = 0;
    for (int i = nums.size() - 1; i >= 0; i--) {
      int v = nums[i];
      ans = max(ans, maxVal - v);
      maxVal = max(maxVal, v);
    }
    return ans == 0 ? -1 : ans;
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