// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  ll X, Y;
  vector<vector<int>> circles;

  tuple<ll, ll, ll> ToCircle(int i) {
    ll x = circles[i][0];
    ll y = circles[i][1];
    ll r = circles[i][2];
    return {x, y, r};
  }
  bool Cross(int a, int b) {
    auto [x0, y0, r0] = ToCircle(a - 1);
    auto [x1, y1, r1] = ToCircle(b - 1);
    return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) <=
           (r0 + r1) * (r0 + r1);
  }
  bool IsLeftTop(int a) {
    auto [x0, y0, r0] = ToCircle(a - 1);
    return x0 - r0 <= 0 || y0 + r0 >= Y;
  }
  bool IsRightDown(int a) {
    auto [x0, y0, r0] = ToCircle(a - 1);
    return x0 + r0 >= X || y0 - r0 <= 0;
  }

  vector<vector<int>> g;
  vector<int> flag;
  const int S = 0;
  int T = 0;
  int n;
  bool Check(int a, const int dst) {
    if (a == dst) {
      return true;
    }
    if (flag[a]) return false;
    flag[a] = 1;
    for (auto b : g[a]) {
      if (Check(b, dst)) {
        return true;
      }
    }
    return false;
  }
  void Add(int a, int b) {
    // printf("%d--%d\n", a, b);
    g[a].push_back(b);
    g[b].push_back(a);
  }

 public:
  bool canReachCorner(int X_, int Y_, vector<vector<int>>& circles_) {
    X = X_;
    Y = Y_;
    circles.swap(circles_);
    n = circles.size();
    T = n + 1;
    // printf("S=%d T=%d\n", S, T);
    g.resize(n + 2);

    for (int i = 1; i <= n; i++) {
      if (IsLeftTop(i)) {
        Add(S, i);
      }
      if (IsRightDown(i)) {
        Add(T, i);
      }
      for (int j = i + 1; j <= n; j++) {
        if (Cross(i, j)) {
          Add(j, i);
        }
      }
    }

    // DFS 判断是否存在从 0 到 n 的路径
    flag.resize(n + 2, 0);
    return !Check(S, T);
  }
};