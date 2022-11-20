#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
class Solution {
  //  (x/y - 1)/2
  //= (x - y)/(y*2)
  double Down(double a) {
    if (a <= 1) {
      return 0;
    }
    return (a - 1) / 2;
  }

  //   ax/ay + bx/by
  // = (ax * by + bx * ay) / (ay * by)
  double Add(const double a, const double b) {
    auto ax = Down(a);
    auto bx = Down(b);
    return ax + bx;
  }

 public:
  double champagneTower(ll poured, int query_row, int query_glass) {
    vector<vector<double>> dp(111, vector<double>(111));

    double zero = 0;
    dp[0][0] = poured;
    for (int i = 1; i <= query_row; i++) {
      dp[i][0] = Add(dp[i - 1][0], zero);
      for (int j = 1; j <= i; j++) {
        dp[i][j] = Add(dp[i - 1][j - 1], dp[i - 1][j]);
      }
    }

    return min(1.0, dp[query_row][query_glass]);
  }
};