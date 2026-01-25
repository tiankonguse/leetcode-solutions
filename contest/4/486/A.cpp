
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
  int minimumPrefixLength(vector<int>& nums) {
    ll lastVal = INT64_MAX;
    int n = nums.size();
    for (int i = n - 1; i >= 0; i--) {
      if (nums[i] >= lastVal) {
        return i + 1;
      }
      lastVal = nums[i];
    }
    return 0;
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