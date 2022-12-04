#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
 public:
  ll dividePlayers(vector<int>& skill) {
    int n = skill.size() / 2;
    ll sum = 0;
    unordered_map<ll, ll> m;
    for (ll v : skill) {
      m[v]++;
      sum += v;
    }

    if (sum % n != 0) return -1;

    ll avg = sum / n;
    ll ans = 0;
    for (auto& [v, c] : m) {
      if (c == 0) continue;
      if (v * 2 == avg) {
        if (c % 2 != 0) return -1;
        ans += v * v * c / 2;
        c = 0;
      } else {
        ll V = avg - v;
        if (m.count(V) == 0) return -1;
        if (m[V] < c) return -1;

        ans += v * V * c;

        m[V] -= c;
        c = 0;
      }
    }
    return ans;
  }
};