// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> tree;
  vector<int> price;
  int n;
  vector<ll> val;  // 以 0 为根的子树最优答案
  vector<vector<ll>> top2;

  ll Dfs0(int r, int p) {
    ll childMax = 0;
    for (int c : tree[r]) {
      if (c == p) continue;
      ll v = Dfs0(c, r);

      top2[r][2] = v;
      for (int i = 1; i >= 0; i--) {
        if (top2[r][i] < top2[r][i + 1]) {
          swap(top2[r][i], top2[r][i + 1]);
        }
      }

      childMax = max(childMax, v);
    }
    return val[r] = price[r] + childMax;
  }

  ll ans;

  void Dfs1(int r, int p, ll preVal) {
    // 以 r 为根

    ans = max(ans, preVal);
    ans = max(ans, top2[r][0]);

    for (int c : tree[r]) {
      if (c == p) continue;
      ll v = top2[r][0];
      if (v == val[c]) {
        v = top2[r][1];
      }
      v = max(v, preVal);
      Dfs1(c, r, v + price[r]);
    }
  }

 public:
  ll maxOutput(int n_, vector<vector<int>>& edges, vector<int>& price_) {
    n = n_;
    price.swap(price_);
    tree.resize(n);
    for (auto& v : edges) {
      int a = v[0], b = v[1];
      tree[a].push_back(b);
      tree[b].push_back(a);
    }

    val.resize(n, 0);
    top2.resize(n, vector<ll>(3, 0));

    Dfs0(0, -1);

    ans = val[0] - price[0];

    Dfs1(0, -1, 0);

    return ans;
  }
};
