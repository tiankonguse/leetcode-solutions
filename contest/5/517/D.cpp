
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 994 / 999 个通过的测试用例©leetcode

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const int MaxVal = 1e9;
class Solution {
  vector<vector<int>> dp;
  vector<vector<pair<int, int>>> g;  // <val, times>
  int Dfs(int i, int sum) {
    int& ret = dp[i][sum];
    if (ret != -1) {
      return ret;
    }
    ret = MaxVal;
    if (i == 0) {
      return ret;  // 只有 dp[0][0] 合法
    }
    // 不选择
    ret = min(ret, Dfs(i - 1, sum));

    for (auto [v, t] : g[i - 1]) {
      if (v > sum) break;
      ret = min(ret, Dfs(i - 1, sum - v) + t);
    }
    return ret;
  }

  void Add(int i, int v, int sum, int t) {
    if (v == 0) return;
    for (int V = v; V <= sum; V *= 2, t++) {
      g[i].push_back({V, t});
    }
  }

 public:
  int minOperations(vector<int>& nums, const int sum) {
    int n = nums.size();
    g.resize(n);
    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      Add(i, v * 2, sum, 1);
      for (int V = v, t = 0; V > 0; V /= 2, t++) {
        g[i].push_back({V, t});
        if (V % 2 == 1) {
          Add(i, V / 2 * 2, sum, t + 2);
        }
      }
      sort(g[i].begin(), g[i].end());
    }
    dp.resize(n + 1, vector<int>(sum + 1, -1));
    dp[0][0] = 0;
    int ans = Dfs(n, sum);
    if (ans == MaxVal) {
      ans = -1;
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