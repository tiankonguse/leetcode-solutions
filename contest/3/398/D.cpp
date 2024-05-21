// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  // tuple<K, jump, op>
  const ll one = 1;
  map<tuple<ll, ll, int>, ll> h;
  void Add(ll k, ll jump, int op, ll ans) {
    tuple<ll, ll, int> p = {k, jump, op};
    h[p] = ans;
  }
  int Dfs(ll k, ll jump, int op) {
    if (k < 0) return 0;
    tuple<ll, ll, int> p = {k, jump, op};
    if (h.count(p)) return h[p];
    auto& ans = h[p];
    ll mask = 1 << jump;

    ans = 0;

    if (op == 0) {
      ans += Dfs(k + 1, jump, 1);
    } else {
      if (jump) {
        ll op = one << (jump - 1);
        ans += Dfs(k - op, jump - 1, 1);
        ans += Dfs(k - op, jump - 1, 0);
      }
    }

    // printf("k=%lld jump=%lld op=%d ans=%lld\n", k, jump, op, ans);

    return ans;
  }

 public:
  int waysToReachStair(int k) {
    ll ans = 0;
    Add(1, 0, 1, 1);
    for (int jump = 0; jump < 32; jump++) {
      ans += Dfs(k, jump, 0);
      ans += Dfs(k, jump, 1);
    }
    return ans;
  }
};
