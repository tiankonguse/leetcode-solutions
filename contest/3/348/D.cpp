// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
ll dp[25][444][444];
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  void fix(string& num, int n) {
    std::reverse(num.begin(), num.end());
    num.resize(n, '0');
    std::reverse(num.begin(), num.end());
  }
  string num1;
  string num2;
  int min_sum;
  int max_sum;
  ll ans = 0;
  int n;

  void Check(int preSum) {
    if (min_sum <= preSum && preSum <= max_sum) {
      ans = (ans + 1) % mod;
    }
  }

  ll Solver(int n, int l, int r) {
    ll& ret = dp[n][l][r];
    if (ret != -1) return ret;
    ret = 0;
    if (n == 1) {
      r = min(r, 9);
      if (l <= r) {
        ret = r - l + 1;
      }
      return ret;
    }

    for (int i = 0; i < 10; i++) {
      if (i > r) break;
      ret = (ret + Solver(n - 1, max(l - i, 0), r - i)) % mod;
    }
    return ret;
  }

  void DfsMid(int p, int preSum) {
    if (p == n) {
      Check(preSum);
      return;
    }
    int len = n - p;
    if (preSum > max_sum) return;            //大于最大值
    if (preSum + len * 9 < min_sum) return;  // 小于最小值
    ans = (ans + Solver(len, max(min_sum - preSum, 0), max_sum - preSum));
  }

  void DfsLow(int p, int preSum) {
    if (p == n) {
      Check(preSum);
      return;
    }
    int v1 = num1[p] - '0';
    DfsLow(p + 1, preSum + v1);
    for (int v = v1 + 1; v < 10; v++) {
      DfsMid(p + 1, preSum + v);
    }
  }
  void DfsHigh(int p, int preSum) {
    if (p == n) {
      Check(preSum);
      return;
    }
    int v2 = num2[p] - '0';
    for (int v = 0; v < v2; v++) {
      DfsMid(p + 1, preSum + v);
    }
    DfsHigh(p + 1, preSum + v2);
  }

  void DfsEq(int p, int preSum) {
    if (p == n) {
      Check(preSum);
      return;
    }
    int v1 = num1[p] - '0';
    int v2 = num2[p] - '0';
    if (v1 == v2) {
      DfsEq(p + 1, preSum + v1);
      return;
    }

    DfsLow(p + 1, preSum + v1);
    for (int v = v1 + 1; v < v2; v++) {
      DfsMid(p + 1, preSum + v);
    }
    DfsHigh(p + 1, preSum + v2);
  }

 public:
  int count(string num1_, string num2_, int min_sum_, int max_sum_) {
    min_sum = min_sum_;
    max_sum = max_sum_;
    num1.swap(num1_);
    num2.swap(num2_);

    memset(dp, -1, sizeof(dp));
    n = num2.size() + 1;
    fix(num1, n);
    fix(num2, n);

    DfsEq(0, 0);
    return ans;
  }
};