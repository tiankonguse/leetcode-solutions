// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
  min_queue<pair<ll, ll>> que;  // <step, val>
  unordered_map<ll, ll> m;
  unordered_map<ll, ll> h;  // 预估的最优答案
  ll ans;

 public:
  int leastOpsExpressTarget(ll x, ll target) {
    ans = target * 2 - 1;  // target 个 x/x 相加

    if (x == target) return 0;  // x
    if (target == 1) return 1;  // x/x

    ll base = 1;
    int t = 0;
    while (base <= target * x) {
      base *= x;
      t++;
      m[base] = t;
    }
    m[1] = 2;

    h[0] = 0;
    que.push({0, 0});

    while (!que.empty()) {
      const auto [step, now] = que.top();
      que.pop();
      if (step >= ans) break;

      // 贪心，大了只能减，小了只能加
      ll sign = 1;
      if (now > target) {
        sign = -1;
      }
      for (auto [base, t] : m) {
        ll tmp = now + sign * base;
        if (tmp < 0) continue;
        ll tmpCost = step + t;
        ll tmpAns = tmpCost + abs(target - tmp) * 2;
        ans = min(tmpAns, ans);
        if (tmpCost < ans && h.count(tmp) == 0) {
          h[tmp] = tmpCost;
          que.push({tmpCost, tmp});
        }
      }
    }
    return ans;
  }
};