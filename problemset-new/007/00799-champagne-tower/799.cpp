#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

// 朴素 GCD/gcd 算法，复杂度 Log(n))
ll Gcd(ll x, ll y) {
  if (!x || !y) return x ? x : y;

  ll t = x - x/ y * y;
  while (t != 0) {
    x = y;
    y = t;
    t = x - x/ y * y;
  }
  return y;
}

// typedef long long ll;
typedef pair<ll, ll> pll;
class Solution {
  pll Smp(pll a) {
    auto [x, y] = a;
    if (x == 0) {
      return {0, 0};
    }
    ll c = Gcd(x, y);
    return {x / c, y / c};
  }

  //  (x/y - 1)/2
  //= (x - y)/(y*2)
  pll Down(pll a) {
    auto [x, y] = a;
    if (x <= y) {
      return {0, 0};
    }
    return Smp({x - y, y * 2});
  }

  //   ax/ay + bx/by
  // = (ax * by + bx * ay) / (ay * by)
  pll Add(const pll a, const pll b) {
    auto [ax, ay] = Down(a);
    auto [bx, by] = Down(b);
    // printf("a={%lld,%lld}, down={%lld, %lld}\n", a.first, a.second, ax, ay);
    // printf("b={%lld,%lld}, down={%lld, %lld}\n", b.first, b.second, bx, by);

    if (ax == 0) {
      return {bx, by};
    } else if (bx == 0) {
      return {ax, ay};
    }

    ll c = Gcd(ay, by);
    ll cx = by/c * ax  + ay/c *bx;
    ll cy =  ay/c * by;

    return Smp({cx ,cy});
  }
  void dump(int i, int j, pll p) {
    // printf("[%d,%d]=>{%lld, %lld}\n", i, j, p.first, p.second);
  }

 public:
  double champagneTower(ll poured, int query_row, int query_glass) {
    vector<vector<pll>> dp(111, vector<pll>(111));

    pll zero = {0, 0};
    dp[0][0] = {poured, 1};
    dump(0, 0, dp[0][0]);
    for (int i = 1; i <= query_row; i++) {
      dp[i][0] = Add(dp[i - 1][0], zero);
      dump(i, 0, dp[i][0]);
      for (int j = 1; j <= i; j++) {
        dp[i][j] = Add(dp[i - 1][j - 1], dp[i - 1][j]);
        dump(i, j, dp[i][j]);
      }
    }

    auto [x, y] = dp[query_row][query_glass];
    if (x == 0) {
      return 0;
    } else if (x >= y) {
      return 1;
    } else {
      return x * 1.0 / y;
    }
  }
};