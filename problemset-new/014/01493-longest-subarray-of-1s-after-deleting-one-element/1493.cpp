
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
  int longestSubarray(vector<int>& nums) {
    // 等价于最多允许1个0
    int n = nums.size();
    int l = 0, r = 0;
    int ans = 0;
    int zeroCount = 0;
    while (r < n) {
      int v = nums[r]; // 第一步：移动右指针
      r++;
      if (v == 0) {
        zeroCount++;
      }
      
      while (zeroCount > 1) { // 第二步：移动左指针
        int v = nums[l];
        l++;
        if (v == 0) {
          zeroCount--;
        }
      }
      ans = max(ans, r - l - 1); // 第三步：更新答案
    }

    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 3);
  return 0;
}

#endif