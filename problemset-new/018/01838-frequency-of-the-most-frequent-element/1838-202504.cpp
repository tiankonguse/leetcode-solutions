
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
  int maxFrequency(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int l = 0, r = 0;
    int ans = 0;
    long long total = 0;
    auto updateRight = [&](const int v) { total += v; };
    auto updateLeft = [&](const int v) { total -= v; };
    auto shouldMoveLeft = [&](const ll rv) -> bool { return total + k < (r - l) * rv; };
    while (r < n) {
      const int rv = nums[r];
      r++;
      updateRight(rv);  // 第一步：移动右指针

      while (shouldMoveLeft(rv)) {  // 第二步：移动左指针
        const int lv = nums[l];
        l++;
        updateLeft(lv);
      }

      ans = max(ans, r - l);  // 第三步：更新答案
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