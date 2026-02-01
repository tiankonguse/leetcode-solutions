
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
enum { UP = 0, DOWN = 1 };
class Solution {
 public:
  int longestAlternating(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> pre(n + 2, vector<int>(2, 1));
    vector<vector<int>> suf(n + 2, vector<int>(2, 1));

    int ans = 1;
    for (int i = 2; i <= n; i++) {
      int nowVal = nums[i - 1];
      int preVal = nums[i - 2];
      if (nowVal > preVal) {
        pre[i][UP] = pre[i - 1][DOWN] + 1;
      } else if (nowVal < preVal) {
        pre[i][DOWN] = pre[i - 1][UP] + 1;
      }
      ans = max(ans, max(pre[i][UP], pre[i][DOWN]));
    }
    for (int i = n - 1; i >= 1; i--) {
      int nowVal = nums[i - 1];
      int sufVal = nums[i];
      if (nowVal > sufVal) {
        suf[i][UP] = suf[i + 1][DOWN] + 1;
      } else if (nowVal < sufVal) {
        suf[i][DOWN] = suf[i + 1][UP] + 1;
      }
      ans = max(ans, max(suf[i][UP], suf[i][DOWN]));
    }
    for (int i = 2; i < n; i++) {
      int preVal = nums[i - 2];
      int sufVal = nums[i];
      if (preVal > sufVal) {
        ans = max(ans, pre[i - 1][UP] + suf[i + 1][DOWN]);
      } else if (preVal < sufVal) {
        ans = max(ans, pre[i - 1][DOWN] + suf[i + 1][UP]);
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