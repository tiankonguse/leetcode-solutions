// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<pair<ll, ll>> m;
  unordered_map<ll, ll> h;  // 预估的最优答案
  ll ans;
  ll X, T;

  map<pair<int, ll>, int> dp;

  ll Dfs(const int t, const ll pre) {
    pair<int, ll> k = {t, pre};
    if (dp.count(k)) return dp[k];
    if (pre == T) return dp[k] = 0;

    ll XT = m[t].first;
    ll COST = m[t].second;
    ll NEXT_L = 1 - XT;
    ll NEXT_R = XT - 1;

    if (t == 0) {
      ll now = abs(T - pre);
      return dp[k] = now * COST;
    }

    // X^t 可以选择 [0, x)个，但是选择后必须保证有答案
    ll sign = 1;
    if (pre > T) {  // 需要减法
      sign = -1;
    }
    ll ans = INT_MAX;
    for (ll i = 0; i < X; i++) {
      ll now = pre + sign * i * XT;
      if (T - now < NEXT_L || NEXT_R < T - now) continue;  //无解
      ll tmpAns = Dfs(t - 1, now) + i * COST;
      printf("pre(%lld) %c %lld*%lld^%lld = %lld\n", pre, sign > 0 ? '+' : '-',
             i, X, T, tmpAns);
      ans = min(ans, tmpAns);
    }
    printf("pre(%lld) t=%d ans=%lld\n", pre, t, ans);
    return dp[k] = ans;
  }

 public:
  int leastOpsExpressTarget(const ll x, const ll target) {
    if (target == 1) return 1;  // x/x

    X = x;
    T = target;

    int t = 0;
    ll base = 1;  // x^t
    m.push_back({1, 2});
    while (base <= target) {
      base *= X;
      t++;
      printf("t=%d base=%lld\n", t, base);
      m.push_back({base, t});
    }
    return Dfs(t, 0);
  }
};