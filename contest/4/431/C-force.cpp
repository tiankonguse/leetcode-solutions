
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
 public:
  ll maximumCoins(vector<vector<int>>& coins, int k) {
    sort(coins.begin(), coins.end());
    int maxV = 0;
    for (auto& coin : coins) {
      maxV = max(maxV, coin[1] + 1);
    }

    vector<ll> nums(maxV, 0);
    for (auto& coin : coins) {
      const ll l = coin[0], r = coin[1], v = coin[2];
      for (ll i = l; i <= r; i++) {
        nums[i] = v;
      }
    }

    vector<ll> preSum(maxV, 0);
    for (int i = 1; i < maxV; i++) {
      preSum[i] = preSum[i - 1] + nums[i];
    }

    ll ans = 0;
    for (int l = 1; l < maxV; l++) {
      int r = min(l + k - 1, maxV - 1);
      ll tmp = preSum[r] - preSum[l - 1];
      if (tmp > ans) {
        printf("tmp=%lld l=%d r=%d\n", tmp, l, r);
        ans = tmp;
      }
    }

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