
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
  vector<vector<pair<ll, int>>> orderStack;
  vector<vector<ll>> dp;

  ll Dfs(int p, int k) {
    if (p < 0 || k <= 0) return 0;
    ll& ret = dp[p][k];
    if (ret != -1) return ret;
    ret = 0;
    if (k == 1) {
      ret = orderStack[p].back().first;
      return ret;
    }
    for (auto& [score, nextP] : orderStack[p]) {
      ret = max(ret, score + Dfs(nextP - 1, k - 1));
    }
    return ret;
  }

  ll Solver(int k) {  //
    // 预处理
    orderStack.resize(n + 1);
    for (int i = 0; i < n; i++) {
      // 得分定义: max - min
      ll maxVal = nums2[i];
      ll minVal = nums2[i];
      orderStack[i].clear();
      orderStack[i].emplace_back(maxVal - minVal, i);  // 默认是自身，得 0 分
      for (int j = i - 1; j >= 0; j--) {
        minVal = min(minVal, nums2[j]);
        maxVal = max(maxVal, nums2[j]);
        if (orderStack[i].back().first < maxVal - minVal) {
          orderStack[i].emplace_back(maxVal - minVal, j);
        }
      }
    }
    dp.clear();
    dp.resize(n + 1, vector<ll>(k + 1, -1));
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

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif