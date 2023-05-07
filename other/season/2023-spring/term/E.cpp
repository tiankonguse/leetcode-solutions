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
TreeArray treeArray[32];
class Solution {
  int n;
  int K;

  void Set(int i, int V) {
    for (int k = 0; k < K; k++) {
      int v = (V >> k) & 1;
      treeArray[k].Add(i, v);
    }
  }
  void Reset(int i, int V) {
    for (int k = 0; k < K; k++) {
      int v = (V >> k) & 1;
      treeArray[k].Add(i, -v);
    }
  }

 public:
  int getNandResult(int k, vector<int>& arr, vector<vector<int>>& operations) {
    K = k;
    n = arr.size();
    for (int k = 0; k < K; k++) {
      treeArray[k].Init(n);
    }

    for (int i = 1; i <= n; i++) {
      Set(i, arr[i - 1]);
    }

    int ans = 0;
    for (auto& v : operations) {
      const ll t = v[0];
      const ll x = v[1];
      const ll y = v[2];
      if (t == 0) {
        Reset(x+1, arr[x]);
        arr[x] = y;
        Set(x+1, arr[x]);
        continue;
      }

      if (x > 0) {
        int Y = 0;
        for (int k = 0; k < K; k++) {
          int v = (y >> k) & 1;
          int V = 0;
          if (treeArray[k].Query(1, n) == n) {  // 全是 1
            ll xn = (x * n) % 2;                // v 与 xn 个 1运算
            V = (v ^ xn);
          } else if (treeArray[k].Query(1, n) == 0) {  //全是 0
            V = 1;
          } else {                 // 0 前面的都没有意义
            int l = 1, r = n+1;  //[l, r]
            while (l < r) {
              int mid = (l + r) / 2;
              int midN = treeArray[k].Query(mid, n);
              if (midN == n - mid + 1) {  // 全是 1,0 在左边
                r = mid;
              } else {  // [mid, n] 之间有 0
                l = mid + 1;
              }
            }
            // 此时 [r, n] 都是 1， r-1 是 0
            ll xn = (n - r + 1) % 2;
            V = 1 - xn;
          }

          Y = Y | (V << k);
        }
        ans = ans ^ Y;
      } else {
        ans = ans ^ y;
      }
    }
    return ans;
  }
};
