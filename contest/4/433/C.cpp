
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
  vector<ll> dp[3][3];
  vector<vector<int>> cost;
  int n;
  ll CalCost(int p, int a, int b) { return cost[p][a] + cost[n - 1 - p][b]; }
  ll Dfs(int p, int a, int b) {
    ll& ret = dp[a][b][p];
    if (ret != -1) return ret;
    ret = __LONG_LONG_MAX__;
    const ll baseCost = CalCost(p, a, b);
    if (p > 0) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (i == j) continue;
          if (i == a || j == b) continue;
          ret = min(ret, baseCost + Dfs(p - 1, i, j));
        }
      }
    } else {
      ret = baseCost;
    }

    return ret;
  }

 public:
  ll minCost(int n, vector<vector<int>>& cost_) {
    cost.swap(cost_);
    this->n = n;
    int nn = n / 2;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        dp[i][j].resize(nn, -1);
      }
    }
    ll ans = __LONG_LONG_MAX__;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == j) continue;
        ans = min(ans, Dfs(nn - 1, i, j));
      }
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {  //
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif