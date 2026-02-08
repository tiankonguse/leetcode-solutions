
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
  int dominantIndices(vector<int>& nums) {
    int n = nums.size();
    vector<int> sufSum(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
      sufSum[i] = nums[i] + sufSum[i + 1];
    }
    int ans = 0;
    for (int i = n - 2; i >= 0; i--) {
      int sum = sufSum[i + 1];
      int cnt = n - 1 - i;
      if (nums[i] * cnt > sum) {
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