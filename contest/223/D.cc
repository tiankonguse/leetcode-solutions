#include "base.h"

typedef long long ll;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// const int mod = 1e9 + 7;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

// lower_bound 大于等于
// upper_bound 大于

const LL INF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2100, max4 = 11100, max5 = 200100, max6 = 2000100;
class Solution {
 public:
  int minimumTimeRequired(vector<int>& jobs, int k) {
    int n = jobs.size();

    vector<vector<int>> dp;
    dp.resize(k);
    dp[0].resize(1 << n, 0);
    for (int mask = 1; mask < (1 << n); mask++) {
      int pre = mask & (mask - 1);
      int now = __builtin_popcount(mask ^ (mask - 1));
      dp[0][mask] = dp[0][pre] + jobs[now - 1];
    }

    for (int i = 1; i < k; i++) {
      dp[i].resize(1 << n, 0);
      for (int mask = 1; mask < (1 << n); mask++) {
        // 前 i 个人，选择 mask 的最优解

        int now = dp[i - 1][mask];
        for (int j = mask; j; j = (j - 1) & state) {
          now = min(now, max(dp[0][j], dp[i - 1][mask ^ j]));
        }
        dp[i][mask] = now;
      }
    }
    return dp[k - 1][(1 << n) - 1];
  }
};
int main() {
  // TEST_SMP2(Solution, get, 0, 1, 1);

  return 0;
}
