
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
  int smallestDivisor(vector<int>& nums, int threshold) {
    int l = 1, r = 10e6;
    while (l < r) {
      int mid = (l + r) / 2;
      int sum = 0;
      for (int i = 0; i < nums.size(); i++) {
        sum += (nums[i] + mid - 1) / mid;
      }
      if (sum > threshold) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
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