
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

// 1273 / 1274 个通过的测试用例
typedef long long ll;
class Solution {
  vector<ll> nums2;
  vector<vector<vector<ll>>> dp;
  enum { EMPTY = 0, BUY = 1, SELL = 2 };

  ll Dfs(int p, int k, int mode) {
    if (p < 0 || k <= 0) {
      if (mode != EMPTY) {
        return INT64_MIN / 2;  // 无效状态
      }
      return 0;
    }
    ll& ret = dp[p][k][mode];
    if (ret != INT64_MIN) return ret;
    if (mode == 0) {
      ret = Dfs(p - 1, k, 0);                          // 不选当前点
      ret = max(ret, Dfs(p - 1, k, BUY) - nums2[p]);   // 之前是买入，现在需要卖出
      ret = max(ret, Dfs(p - 1, k, SELL) + nums2[p]);  // 之前是卖出，现在需要买入
    } else if (mode == 1) {
      ret = Dfs(p - 1, k, BUY);                             // 不选当前点，继续买入
      ret = max(ret, Dfs(p - 1, k - 1, EMPTY) + nums2[p]);  // 之前是空闲，现在买入
    } else {
      ret = Dfs(p - 1, k, SELL);                            // 不选当前点，继续卖出
      ret = max(ret, Dfs(p - 1, k - 1, EMPTY) - nums2[p]);  // 之前是空闲，现在卖出
    }
    return ret;
  }

  ll Solver(int k) {  //
    int n = nums2.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= k; j++) {
        for (int m = 0; m < 3; m++) {
          dp[i][j][m] = INT64_MIN;
        }
      }
    }
    return Dfs(n - 1, k, EMPTY);
  }

 public:
  long long maximumScore(const vector<int>& nums, int k) {
    int n = nums.size();
    dp.resize(n, vector<vector<ll>>(k + 1, vector<ll>(3, -1)));
    int maxIndex = 0;
    for (int i = 0; i < n; i++) {
      if (nums[i] > nums[maxIndex]) {
        maxIndex = i;
      }
    }
    // case1: maxIndex 是第一个
    nums2.resize(n);
    for (int i = 0, j = maxIndex; i < n; i++, j = (j + 1) % n) {
      nums2[i] = nums[j];
    }
    ll ans1 = Solver(k);
    // case2: maxIndex 是最后一个
    // nums2.resize(n);
    for (int i = 0, j = (maxIndex + 1) % n; i < n; i++, j = (j + 1) % n) {
      nums2[i] = nums[j];
    }
    ll ans2 = Solver(k);
    return max(ans1, ans2);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<int>& nums, int k, const ll& ans) {
  TEST_SMP2(Solution, maximumScore, ans, nums, k);  //
}

int main() {
  {
    vector<int> nums = {1, 3, 4};
    int k = 2;
    ll ans = 3;
    Test(nums, k, ans);
  }
  {
    vector<int> nums = {9, 11, 15, 3, 2, 10, 8};
    int k = 5;
    ll ans = 23;
    Test(nums, k, ans);
  }
  {
    vector<int> nums = {7, 20, 16, 14, 13, 6, 5};
    int k = 6;
    ll ans = 25;
    Test(nums, k, ans);
  }
  {
    vector<int> nums = {1, 1, 2, 2};
    int k = 1;
    ll ans = 1;
    Test(nums, k, ans);
  }
  return 0;
}

#endif