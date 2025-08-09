
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
  bool isTrionic(vector<int>& nums) {
    int n = nums.size();
    int p = -1, q = -1;
    for (int i = 1; i < n; i++) {
      if (nums[i - 1] < nums[i]) {
        p = i;
        continue;
      }
      break;
    }
    if (p == -1 || p == n - 1) return false;
    for (int i = p + 1; i < n; i++) {
      if (nums[i - 1] > nums[i]) {
        q = i;
        continue;
      }
      break;
    }
    if (q == -1 || q == n - 1) return false;
    for (int i = q + 1; i < n; i++) {
      if (nums[i - 1] < nums[i]) {
        continue;
      }
      return false;
    }
    return true;
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