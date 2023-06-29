// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  // 1 <= cost.length <= 500
  // 1 <= cost[i] <= 10^6
  // 1 <= time[i] <= 500
  // useTime >= leftNum
  //  useTime >= n - useNum
  // useTime + useNum >= n
  // sum(oneTime + 1) >= n
  vector<vector<ll>> dp;  // dp[n][sumTime]
  vector<int> cost;
  vector<int> time;

  ll Dfs(int p, int sumTime) {
    if (sumTime <= 0) {
      return 0;
    }
    if (p == -1) {
      return INT_MAX;  // 没有答案
    }

    ll& ret = dp[p][sumTime];
    if (ret != -1) {
      return ret;
    }

    ll ans1 = Dfs(p - 1, sumTime);  // 不选择
    ll ans2 = Dfs(p - 1, sumTime - time[p]) + cost[p];
    return ret = min(ans1, ans2);
  }

 public:
  int paintWalls(vector<int>& cost_, vector<int>& time_) {
    time.swap(time_);
    cost.swap(cost_);
    int n = cost.size();
    dp.resize(n + 1, vector<ll>(n + 1, -1));
    for (auto& t : time) {
      t++;
    }
    return Dfs(n - 1, n);
  }
};