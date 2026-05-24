
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
  vector<int> limitOccurrences(vector<int>& nums, int k) {  //
    int n = nums.size();
    int cnt = 1;
    int idx = 1;
    for (int i = 1; i < n; ++i, ++idx) {
      nums[idx] = nums[i];
      if (nums[i] == nums[idx - 1]) {
        cnt++;
        if (cnt > k) {
          --idx;
        }
      } else {
        cnt = 1;
      }
    }
    nums.resize(idx);
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