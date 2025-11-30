
#include <bits/stdc++.h>

class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_ + 1;
    t1.clear();
    t1.resize(n + 10, 0);
    t2.clear();
    t2.resize(n + 10, 0);
  }

  void AddEx(int l, int r, ll v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  ll Query(int l, int r) {
    return (r + 1ll) * Query(t1, r) - 1ll * l * Query(t1, l - 1) -
           (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  void Add(int k, ll v) {
    ll v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  ll Query(vector<ll>& t, int k) {
    ll ret = 0;
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