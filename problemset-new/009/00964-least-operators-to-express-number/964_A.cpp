// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
class Solution {
  vector<pair<ll, ll>> m;
  min_queue<tuple<ll, ll, ll>> que;  // <expectAns, step, val>
  unordered_map<ll, ll> h;  // <val, step> 到达 v 的最小 step
  ll ans;

  ll getExp(const ll x, const ll target, const ll now){
    ll dis = abs(target - now);
    ll ans = 0;
    while(dis){
      pair<ll, ll> v = {dis, 100};
      auto it = upper_bound(m.begin(), m.end(), v);
      it--;
      ans += it->second;
      dis -= it->first;
    }
    return ans;
  }

 public:
  int leastOpsExpressTarget(const ll x, const ll target) {

    if (x == target) return 0;  // x
    if (target == 1) return 1;  // x/x

    ll base = 1;
    int t = 0;
    m.push_back({1,2});
    while (base <= target * x) {
      base *= x;
      t++;
      m.push_back({base, t});
    }

    h[0] = 0;
    ans = getExp(x, target, 0);  // target 个 x/x 相加
    printf("ans=%lld\n", ans);
    que.push({ans, 0, 0});

    vector<int> signs = {1, -1};

    while (!que.empty()) {
       auto [_, cost, val] = que.top();
      que.pop();
      if(cost > h[val]){
        cost = h[val];
      }
      if (cost >= ans) continue;

      // 贪心，大了只能减，小了只能加
      for(const auto sign: signs){
        for (const auto [base, t] : m) {
          const ll tmpVal = val + sign * base;
          const ll tmpCost = cost + t;
          const ll tmpAns = getExp(x, target, tmpCost);
          ans = min(tmpAns, ans);
          if(tmpAns > ans * 2) continue;
          if(tmpCost >= ans) continue;
          if (h.count(tmpVal) == 0 || h[tmpVal] > tmpCost) {
            h[tmpVal] = tmpCost;
            que.push({tmpAns, tmpCost, tmpVal});
          }
        }
      }

    }
    return ans-1;
  }
};