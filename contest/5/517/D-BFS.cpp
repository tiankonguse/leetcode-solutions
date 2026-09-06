
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif
// 994 / 999 个通过的测试用例

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
      if (v > sum) continue;
      ret = min(ret, Dfs(i - 1, sum - v) + t);
    }
    return ret;
  }

  vector<int> lastPos;
  void Add(int i, int v, int sum, int t) {
    if (v == 0) return;
    for (int V = v; V <= sum; V *= 2, t++) {
      if (lastPos[V] == i) break;
      lastPos[V] = i;
      g[i].push_back({V, t});
    }
  }
  int maxVal;
  void Bfs(const int i, const int v, const int sum) {
    queue<pair<int, int>> que;
    auto Add = [&](int V, int t) {
      if (V == 0 || V > maxVal) return;
      if (lastPos[V] == i) return;
      lastPos[V] = i;
      g[i].push_back({V, t});
      que.push({V, t});
    };
    Add(v, 0);

    while (!que.empty()) {
      auto [v, t] = que.front();
      que.pop();
      Add(v * 2, t + 1);
      Add(v / 2, t + 1);
    }
  }

 public:
  int minOperations(vector<int>& nums, const int sum) {
    int n = nums.size();
    g.resize(n);
    maxVal = sum;
    for (auto v : nums) {
      maxVal = max(maxVal, v);
    }
    lastPos.resize(maxVal + 1, -1);
    for (int i = 0; i < n; i++) {
      const int v = nums[i];
      Bfs(i, v, sum);
      sort(g[i].begin(), g[i].end());
      MyPrintf("i=%d, v=%d , g(%d):", i, v, int(g[i].size()));
      for (auto [v, t] : g[i]) MyPrintf(" (%d,%d)", v, t);
      MyPrintf("\n");
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

#endif©leetcode