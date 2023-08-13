// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

template <class T>
class TreeArrayEx {
 public:
  void Init(int n_) {
    n = n_ + 1;
    t1.clear();
    t1.resize(n + 10, 0.0);
    t2.clear();
    t2.resize(n + 10, 0.0);
  }

  void AddEx(int l, int r, T v) {
    Add(l, v);
    Add(r + 1, -v);  // 将区间加差分为两个前缀加
  }

  T Query(int l, int r) {
    T one = 1;
    return (r + one) * Query(t1, r) - one * l * Query(t1, l - 1) -
           (Query(t2, r) - Query(t2, l - 1));
  }

 private:
  void Add(int k, T v) {
    T v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += Lowbit(k);
    }
  }
  double Query(vector<T>& t, int k) {
    T ret = 0;
    while (k) {
      ret += t[k];
      k -= Lowbit(k);
    }
    return ret;
  }
  int Lowbit(int x) { return x & -x; }
  vector<T> t1, t2;
  int n;
};

TreeArrayEx<long double> treeArray;
class Solution {
 public:
  double new21Game(int n, int k, int maxPts) {
    if (k == 0) return 1.0;
    treeArray.Init(n + 1);

    for (int i = 0; i < k; i++) {
      long double v = 0;
      if (i == 0) {
        v = 1;
      } else {
        v = treeArray.Query(i, i);
      }
      int l = i + 1;
      int r = min(n, i + maxPts);
      treeArray.AddEx(l, r, v / maxPts);
    }
    return treeArray.Query(k, n);
  }
};