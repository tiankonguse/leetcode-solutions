
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
  vector<bool> subsequenceSumAfterCapping(vector<int>& nums, const int k) {
    int n = nums.size();
    vector<bool> ans(n, false);
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    sort(nums.begin(), nums.end());
    int p = 0;
    auto Add = [&](int v) {
      if (dp[k] == 1) {
        return;
      }
      for (int i = k; i >= 0; i--) {
        if (dp[i] == 1 && i + v <= k) {
          dp[i + v] = 1;
        }
      }
    };
    auto Check = [&](int leftNum, int x) {
      if (dp[k] == 1) return true;
      for (int i = 1; i <= leftNum; i++) {
        if (i * x > k) return false;
        if (dp[k - i * x] == 1) return true;
      }
      return false;
    };
    for (int x = 1; x <= n; x++) {
      while (p < n && nums[p] <= x) {
        Add(nums[p]);
        p++;
      }
      ans[x - 1] = Check(n - p, x);
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