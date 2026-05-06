
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
  ll Cal(ll a, ll b, ll c) {
    ll ac = max(a, c);
    ll tmp = 0;
    if (b <= ac) {
      tmp = ac - b + 1;
    }
    return tmp;
  }

 public:
  int minOperations(vector<int>& nums, const int k) {
    if (k == 0) {
      return 0;
    }
    int n = nums.size();
    const int num = n / 2;
    if (num < k) {
      return -1;
    }
    nums.push_back(nums[0]);
    auto V = [&](int i) -> ll { return nums[i - 1]; };

    // case1: nums[0] 是波峰： nums[0] > nums[-1]
    auto Solver1 = [&]() -> ll {  //
      vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
      dp[0][0] = dp[0][1] = dp[0][2] = 0;
      dp[1][2] = Cal(nums[n - 1], nums[0], nums[1]);
      for (int j = 3; j <= n; j++) {
        dp[0][j] = 0;
        for (int i = 1; i <= k; i++) {
          dp[i][j] = dp[i][j - 1];
          if (dp[i - 1][j - 2] != INT64_MAX) {  // 选择 j 当做波谷
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 2] + Cal(V(j - 2), V(j - 1), V(j)));
          }
        }
      }
      return dp[k][n];
    };
    // case2: nums[0] 是波谷： nums[0] < nums[-1]
    auto Solver2 = [&]() -> ll {  //
      vector<vector<ll>> dp(k + 1, vector<ll>(n + 2, INT64_MAX));
      dp[0][0] = dp[0][1] = dp[0][2] = 0;
      for (int j = 3; j <= n + 1; j++) {
        dp[0][j] = 0;
        for (int i = 1; i <= k; i++) {
          dp[i][j] = dp[i][j - 1];
          if (dp[i - 1][j - 2] != INT64_MAX) {  // 选择 j 当做波谷
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 2] + Cal(V(j - 2), V(j - 1), V(j)));
          }
        }
      }
      return dp[k][n + 1];
    };
    // case3: nums[0] 不与 nums[-1] 比较
    auto Solver3 = [&]() -> ll {  //
      vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
      dp[0][0] = dp[0][1] = dp[0][2] = 0;
      for (int j = 3; j <= n; j++) {
        dp[0][j] = 0;
        for (int i = 1; i <= k; i++) {
          dp[i][j] = dp[i][j - 1];
          if (dp[i - 1][j - 2] != INT64_MAX) {  // 选择 j 当做波谷
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 2] + Cal(V(j - 2), V(j - 1), V(j)));
          }
        }
      }
      return dp[k][n];
    };
    ll ans = INT64_MAX;
    ans = min(ans, Solver1());
    ans = min(ans, Solver2());
    ans = min(ans, Solver3());
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