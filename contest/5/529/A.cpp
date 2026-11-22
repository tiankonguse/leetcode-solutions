
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
  int countDominantElements(vector<int>& nums) {
    int n = nums.size();
    int ans = 0;
    if (n == 1) return 1;
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        if (nums[i] >= nums[i + 1]) ans++;
      } else if (i + 1 == n) {
        if (nums[i] >= nums[i - 1]) ans++;
      } else {
        if (nums[i] * 2 >= nums[i - 1] + nums[i + 1]) ans++;
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