
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 0;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
class Solution {
  ll ans = 0;

  void Solver(vector<vector<int>>& coins, int k) {
    int n = coins.size();
    sort(coins.begin(), coins.end());

    vector<ll> preSum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      const auto& coin = coins[i - 1];
      const ll l = coin[0], r = coin[1], v = coin[2];
      preSum[i] = preSum[i - 1] + v * (r - l + 1);
    }

    for (int i = 1; i <= n; i++) {  // 枚举左边界
      const ll l = coins[i - 1][0];
      ll r = l + k - 1;
      auto it = upper_bound(coins.begin(), coins.end(), r, [](int R, const auto& coin) {
        return R <= coin[1];  //
      });
      if (it == coins.end()) {
        ans = max(ans, preSum[n] - preSum[i - 1]);  // 选择区间 [i,n] 的所有点
      } else {
        int j = it - coins.begin() + 1;
        const auto& coin = coins[j - 1];
        const ll L = coin[0], V = coin[2];
        if (L <= r) {
          ans = max(ans, preSum[j - 1] - preSum[i - 1] + V * (r - L + 1));
        } else {
          ans = max(ans, preSum[j - 1] - preSum[i - 1]);
        }
      }
    }
  }

 public:
  ll maximumCoins(vector<vector<int>>& coins, int k) {
    Solver(coins, k);  // 正序
    for (auto& coin : coins) {
      const ll l = coin[0], r = coin[1];
      coin[0] = -r;
      coin[1] = -l;
    }
    Solver(coins, k);  // 正序
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(vector<vector<int>> coins, int k, ll ans) {  //
  TEST_SMP2(Solution, maximumCoins, ans, coins, k);
}

int main() {
  Test({{35, 37, 15},
        {3, 9, 1},
        {31, 33, 20},
        {10, 15, 6},
        {1, 2, 5},
        {38, 39, 8},
        {20, 23, 16},
        {48, 49, 3},
        {40, 43, 4},
        {29, 30, 16}},
       42, 282);
  return 0;
}

#endif