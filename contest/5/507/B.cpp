
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
  int countValidSubarrays(vector<int>& nums, int x) {  //
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      ll sum = 0;
      for (int j = i; j < n; j++) {
        sum += nums[j];
        ll tmp = sum;
        if (tmp % 10 != x) {
          continue;
        }
        while (tmp >= 10) {
          tmp /= 10;
        }
        if (tmp == x) {
          // MyPrintf("i=%d, j=%d, sum=%lld\n", i, j, sum);
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