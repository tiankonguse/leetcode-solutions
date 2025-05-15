
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
  int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(111, vector<ll>(k + 1, -1)));
    auto Right = [&](auto Right, const int p, const ll v, const int k) -> ll {
      ll& ret = dp[p][v][k];
      if (ret != -1) return ret;
      if (p == n - 1) {
        if (k < 0) {
          return ret = INT_MAX;
        }
        return ret = 0;  // 最后一个
      }
      if (n - 1 - p - 1 < k) {
        return ret = INT_MAX;  // 剪枝，没有答案
      }
      if (k == 0) {
        return ret = (position[p + 1] - position[p]) * (time[p] + v) + Right(Right, p + 1, 0, k);
      }
      ret = INT_MAX;
      ll V = 0;
      for (int i = p + 1; i < n; i++) {  // 第 i 个不删除
        int K = i - p - 1;               // 删除 K 个
        if (K > k) break;

        ll dis = position[i] - position[p];
        ll cost = dis * (time[p] + v);
        ll tmp = Right(Right, i, V, k - K);
        ret = min(ret, cost + tmp);
        V += time[i];  // 删除第 i 个
      }
      return ret;
    };

    return Right(Right, 0, 0, k);
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