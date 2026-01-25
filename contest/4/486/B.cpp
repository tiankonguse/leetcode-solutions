
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
  vector<int> rotateElements(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> tmpNums;
    tmpNums.reserve(n);
    for (int i = 0; i < n; i++) {
      if (nums[i] >= 0) {
        tmpNums.push_back(nums[i]);
      }
    }
    int m = tmpNums.size();
    int offset = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] >= 0) {
        nums[i] = tmpNums[(offset + k) % m];
        offset++;
      }
    }
    return nums;
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