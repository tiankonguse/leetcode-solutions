// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_;
    t1.clear();
    t1.resize(n + 100, 0);
    t2.clear();
    t2.resize(n + 100, 0);
  }

  void AddEx(int l, int r, ll v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  void Add(int k, ll v) {
    ll v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  ll Query(int l, int r) {
    return (r + 1ll) * Query(t1, r) - 1ll * l * Query(t1, l - 1) -
           (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  int Query(vector<ll>& t, int k) {
    int ret = 0;
    while (k) {
      ret += t[k];
      k -= Lowbit(k);
    }
    return ret;
  }
  int Lowbit(int x) { return x & -x; }
  vector<ll> t1, t2;
  int n;
};

class Solution {
 public:
  vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
    vector<TreeArrayEx> rows(n);
    for (int i = 0; i < n; i++) {
      rows[i].Init(n + 1);
    }

    for (auto& q : queries) {
      int r0 = q[0], c0 = q[1];
      int r1 = q[2], c1 = q[3];
      for (int i = r0; i <= r1; i++) {
        rows[i].AddEx(c0 + 1, c1 + 1, 1);
      }
    }

    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ans[i][j] = rows[i].Query(j + 1, j + 1);
      }
    }
    return ans;
  }
};