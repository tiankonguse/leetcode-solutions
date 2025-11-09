
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
  int n;
  vector<vector<ll>> dp;

  ll Dfs(int p, int k) {
    if (p < 0 || k <= 0) return 0;
    ll& ret = dp[p][k];
    if (ret != -1) return ret;
    ret = Dfs(p - 1, k);  // 不选当前点
    // 当前位置当做最大值

    ll minVal = nums2[p];
    for (int j = p - 1; j >= 0; j--) {
      if (nums2[j] >= nums2[p]) {
        break;
      }
      minVal = min(minVal, nums2[j]);
      ret = max(ret, Dfs(j - 1, k - 1) + nums2[p] - minVal);
    }

    // 当前位置当做最小值
    ll maxVal = nums2[p];
    for (int j = p - 1; j >= 0; j--) {
      if (nums2[j] <= nums2[p]) {
        break;
      }
      maxVal = max(maxVal, nums2[j]);
      ret = max(ret, Dfs(j - 1, k - 1) + maxVal - nums2[p]);
    }
    return ret;
  }

  ll Solver(int k) {  //
    // 预处理
    dp.clear();
    dp.resize(n + 1, vector<ll>(k + 1, -1));
    return Dfs(n - 1, k);
  }

 public:
  long long maximumScore(vector<int>& nums, int k) {
    n = nums.size();
    k = min(k, n / 2);
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
  return 0;
}

#endif