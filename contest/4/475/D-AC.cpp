
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
  vector<ll> nums1;
  vector<ll> nums2;
  vector<vector<tuple<ll, int, int>>> maxOrderStack;  // 当前点为结尾的最大值栈
  vector<vector<tuple<ll, int, int>>> minOrderStack;  // 当前点为结尾的最小值栈
  vector<ll> preMax;
  vector<vector<ll>> dp;

  ll Dfs(int p, int k) {
    if (p < 0 || k <= 0) return 0;
    ll& ret = dp[p][k];
    if (ret != -1) return ret;
    if (k == 1 || p <= 2) {
      return ret = preMax[p];
    }
    ret = Dfs(p - 1, k);  // 不选当前点

    // 选最大值栈
    for (auto& [minVal, preIndex, flag] : maxOrderStack[p]) {
      ret = max(ret, Dfs(preIndex - 1, k - 1) + nums2[p] - minVal);
      if (flag && preIndex - 1 <= (k - 1) * 2) {
        break;  // 剪枝
      }
    }
    // 选最小值栈
    for (auto& [maxVal, preIndex, flag] : minOrderStack[p]) {
      ret = max(ret, Dfs(preIndex - 1, k - 1) + maxVal - nums2[p]);
      if (flag && preIndex - 1 <= (k - 1) * 2) {
        break;  // 剪枝
      }
    }
    return ret;
  }

  void CheckAndFix() {
    int m = nums1.size();
    if (m < 5) return;
    // 预期：连续 5 个递增或递减，则删除最中间的一个
    bool inc = true;
    bool dec = true;
    for (int i = m - 5; i < m - 1; i++) {
      if (nums1[i] >= nums1[i + 1]) {
        inc = false;
      }
      if (nums1[i] <= nums1[i + 1]) {
        dec = false;
      }
    }
    if (inc) {
      nums1.erase(nums1.begin() + m - 3);
    }
    if (dec) {
      nums1.erase(nums1.begin() + m - 3);
    }
  }

  ll Solver(int k) {  //
    int n = nums2.size();
    nums1.clear();
    nums1.reserve(n);
    for (auto v : nums2) {
      nums1.push_back(v);
      CheckAndFix();
    }
    nums1.swap(nums2);
    n = nums2.size();

    // 预处理
    maxOrderStack.resize(n + 1);
    minOrderStack.resize(n + 1);
    preMax.resize(n + 1);
    ll maxVal = nums2[0];
    ll minVal = nums2[0];
    for (int i = 0; i < n; i++) {
      maxVal = max(maxVal, nums2[i]);
      minVal = min(minVal, nums2[i]);
      preMax[i] = maxVal - minVal;
    }

    // 当做最大值
    for (int i = 0; i < n; i++) {
      ll maxVal = nums2[i];
      ll minVal = nums2[i];
      auto& sta = maxOrderStack[i];
      sta.clear();
      for (int j = i - 1; j >= 0; j--) {
        if (nums2[j] >= maxVal) {
          break;
        }
        minVal = min(minVal, nums2[j]);
        if (!sta.empty() && nums2[j] > get<0>(sta.back())) {
          get<2>(sta.back())++;
        }
        if (sta.empty() || minVal < get<0>(sta.back())) {
          sta.emplace_back(minVal, j, 0);
        }
      }
    }
    // 当做最小值
    for (int i = 0; i < n; i++) {
      ll maxVal = nums2[i];
      ll minVal = nums2[i];
      auto& sta = minOrderStack[i];
      sta.clear();
      for (int j = i - 1; j >= 0; j--) {
        if (nums2[j] <= minVal) {
          break;
        }
        maxVal = max(maxVal, nums2[j]);
        if (!sta.empty() && nums2[j] < get<0>(sta.back())) {
          get<2>(sta.back())++;
        }
        if (sta.empty() || maxVal > get<0>(sta.back())) {
          sta.emplace_back(maxVal, j, 0);
        }
      }
    }

    dp.clear();
    dp.resize(n, vector<ll>(k + 1, -1));
    return Dfs(n - 1, k);
  }

 public:
  long long maximumScore(const vector<int>& nums, int k) {
    int n = nums.size();
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
    nums2.resize(n);
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