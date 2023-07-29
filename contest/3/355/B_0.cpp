// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class TreeArray {
 public:
  void Init(int n_) {
    n = n_;
    c.clear();
    c.resize(n + 100, 0);
  }

  ll Query(int x) {
    ll s = 0;
    while (x > 0) {
      s += c[x];
      x -= Lowbit(x);
    }
    return s;
  }

  ll Query(int l, int r) { return Query(r) - Query(l - 1); }

  void Add(int x, ll v) {
    while (x <= n) {
      c[x] += v;
      x += Lowbit(x);
    }
  }

 private:
  int Lowbit(int x) { return x & -x; }
  vector<ll> c;
  int n;
};
TreeArray treeArray;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 1000010;
class Solution {
 public:
  long long maxArrayValue(vector<int>& nums) {
    treeArray.Init(max6);
    ll ans = 0;

    for (ll v : nums) {
      treeArray.Add(v, v);
      while (1) {
        ll sum = treeArray.Query(1, min(v, ll(max6 - 1)));
        if (sum == v) {
          break;
        }
        v = sum;
      }
      ans = max(ans, v);
    }

    return ans;
  }
};