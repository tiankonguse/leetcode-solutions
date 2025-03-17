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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
 public:
  int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum == 0) return 0;
    const int n = nums.size();
    const int q = queries.size();
    // printf("n=%d q=%d\n", n, q);
    vector<int> weights(q);
    vector<int> dp(q * 10);
    auto CheckV = [&](int p, int V, int mid) -> bool {  // 检查一个是否满足
      weights.clear();
      // queries 中选择前 mid 个区间
      for (int i = 0; i <= mid; i++) {
        auto& v = queries[i];
        int l = v[0], r = v[1], val = v[2];
        if (p < l || p > r || val > V) continue;
        if (val == V) return true;  // 剪枝
        weights.push_back(val);
      }
      sort(weights.begin(), weights.end());
      //  01背包， V 需要刚好填满
      dp.clear();
      dp.resize(V + 1, 0);
      for (auto v : weights) {
        for (int i = V; i >= v; i--) {
          dp[i] = max(dp[i], dp[i - v] + v);
        }
      }
      return dp[V] == V;
    };
    auto Check = [&](int mid) -> bool {
      for (int i = 0; i < n; i++) {
        int v = nums[i];
        if (v == 0) continue;
        if (CheckV(i, v, mid)) continue;
        return false;
      }
      return true;
    };

    int l = 0, r = q;
    while (l < r) {
      int mid = (l + r) / 2;
      int ret = Check(mid);
      // printf("l=%d r=%d mid=%d ret=%d\n", l, r, mid, ret);
      if (ret) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (l == q) return -1;
    return l + 1;
  }
};

#ifdef USACO_LOCAL_JUDGE

int main() {  //
  return 0;
}

#endif