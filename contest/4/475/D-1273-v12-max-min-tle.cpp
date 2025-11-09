
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
  vector<vector<pair<ll, int>>> maxOrderStack;  // 当前点为结尾的最大值栈
  vector<vector<pair<ll, int>>> minOrderStack;  // 当前点为结尾的最小值栈
  vector<vector<ll>> dp;

  ll Dfs(int p, int k) {
    if (p < 0 || k <= 0) return 0;
    ll& ret = dp[p][k];
    if (ret != -1) return ret;
    ret = Dfs(p - 1, k);  // 不选当前点

    // 选最大值栈
    for (auto& [val, preIndex] : maxOrderStack[p]) {
      ret = max(ret, Dfs(preIndex - 1, k - 1) + val);
    }
    // 选最小值栈
    for (auto& [val, preIndex] : minOrderStack[p]) {
      ret = max(ret, Dfs(preIndex - 1, k - 1) + val);
    }
    return ret;
  }

  ll Solver(int k) {  //
    // 预处理
    maxOrderStack.resize(n + 1);
    minOrderStack.resize(n + 1);

    // 先计算最大值栈
    for (int i = 0; i < n; i++) {
      ll maxVal = nums2[i];
      ll minVal = nums2[i];
      maxOrderStack[i].clear();
      maxOrderStack[i].push_back({maxVal - minVal, i});  // 自身
      for (int j = i - 1; j >= 0; j--) {
        if (nums2[j] >= maxVal) {
          break;
        }
        minVal = min(minVal, nums2[j]);
        if (maxOrderStack[i].back().first < maxVal - minVal) {
          maxOrderStack[i].emplace_back(maxVal - minVal, j);
        }
      }
    }
    // 再计算最小值栈
    for (int i = 0; i < n; i++) {
      ll maxVal = nums2[i];
      ll minVal = nums2[i];
      minOrderStack[i].clear();
      minOrderStack[i].push_back({maxVal - minVal, i});  // 自身
      for (int j = i - 1; j >= 0; j--) {
        if (nums2[j] <= minVal) {
          break;
        }
        maxVal = max(maxVal, nums2[j]);
        if (minOrderStack[i].back().first < maxVal - minVal) {
          minOrderStack[i].emplace_back(maxVal - minVal, j);
        }
      }
    }

    dp.clear();
    dp.resize(n, vector<ll>(k + 1, -1));
    return Dfs(n - 1, k);
  }

 public:
  long long maximumScore(vector<int>& nums, int k) {
    n = nums.size();
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
  vector<int> nums = {1, 3, 4};
  int k = 2;
  ll ans = 3;
  Test(nums, k, ans);
  return 0;
}

#endif