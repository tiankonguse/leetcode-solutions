// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
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

TreeArrayEx treeArray;
class Solution {
  void Add(int x, int y) {
    if (x <= y) {
      // printf("x=%d y=%d\n", x, y);
      treeArray.AddEx(x, y, 1);
    }
  }

 public:
  vector<int> countOfPairs(int n, int x, int y) {
    // printf("init\n");
    treeArray.Init(n + 1);
    if (x > y) {
      swap(x, y);
    }

    // 1->[x, y]->n
    for (int i = 1; i <= n; i++) {
      // printf("i=%d\n", i);
      if (i <= x) {
        Add(1, i - 1);
        Add(1, x - i);

        ll X = x - i;
        ll z = y - x;
        Add(X + 1, X + z / 2);
        Add(X + 1, X + (z + 1) / 2);

        ll Y = X + 1;
        if (x == y) {
          Y--;
        }
        Add(Y + 1, Y + n - y);
      } else if (i >= y) {
        Add(1, n - i);
        Add(1, i - y);

        ll Y = i - y;
        ll z = y - x;
        Add(Y + 1, Y + z / 2);
        Add(Y + 1, Y + (z + 1) / 2);

        ll X = Y + 1;
        if (x == y) {
          X--;
        }
        Add(X + 1, X + x - 1);
      } else {
        ll pre = i - x;
        ll sub = y - i;

        ll minPre = min(pre, sub + 1);
        ll minSub = min(sub, pre + 1);

        Add(minPre + 1, minPre + x - 1);  //[1,x]

        ll z = y - x;  // (x, y)
        Add(1, z / 2);
        Add(1, (z + 1) / 2);

        Add(minSub + 1, minSub + n - y);  // [y, n]
      }
    }

    vector<int> ans(n, 0);
    for (int i = 1; i <= n; i++) {
      ans[i - 1] = treeArray.Query(i, i);
    }
    return ans;
  }
};