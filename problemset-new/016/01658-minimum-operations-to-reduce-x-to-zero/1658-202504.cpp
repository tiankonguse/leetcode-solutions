
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
  int minOperations(vector<int>& nums, int x) {
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum < x) return -1;
    if (sum == x) return n;

    int l = 0, r = 0;
    int ans = -1;
    int cur = 0;
    auto updateRight = [&](int v) { cur += v; };
    auto updateLeft = [&](int v) { cur -= v; };
    auto shouldMoveLeft = [&](int rv) -> bool { return cur > (sum - x); };
    while (r < n) {
      int rv = nums[r];
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (shouldMoveLeft(rv)) {  // 第二步：移动左指针
        int lv = nums[l];
        l++;
        updateLeft(lv);
      }

      if (cur == (sum - x)) {
        ans = max(ans, r - l);  // 第三步：更新答案
      }
    }
    if (ans == -1) return -1;
    ans = n - ans;
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