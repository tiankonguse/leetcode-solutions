
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
  int maximumCount(vector<int>& nums) {
    int n = nums.size();
    int right = upper_bound(nums.begin(), nums.end(), 0) - nums.begin();
    int rightNum = n - right;
    int left = lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
    int leftNum = left;
    return max(leftNum, rightNum);
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