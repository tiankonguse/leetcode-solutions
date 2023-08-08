// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
class Solution {
  vector<vector<ll>> dp;  // dp[b][a] 长度为 a, 前缀为 b ，后缀为任意值的答案
  string low;
  string high;
  ll ans = 0;
  int n;

  int Dis(int a, int b) {
    if (a >= b) {
      return a - b;
    } else {
      return b - a;
    }
  };
  void Update(ll v) { ans = (ans + v) % mod; }

  void DfsEq(int p, int preZero = 1) {
    if (p == -1) {
      Update(1);
      return;
    }

    if (low[p] == high[p]) {  // 最高位依旧相等
      if (p < n - 1 && Dis(low[p], low[p + 1]) != 1) {
        return;  //没有答案
      }

      DfsEq(p - 1, 0);
      return;
    }

    if (p == n - 1 || (p < n - 1 && Dis(low[p], low[p + 1]) == 1)) {
      // printf("has low\n");
      DfsLow(p - 1, preZero && (low[p] == '0'));
    }

    for (char c = low[p] + 1; c < high[p]; c++) {
      if (p == n - 1 || (p < n - 1 && Dis(c, low[p + 1]) == 1)) {
        // printf("mid p=%d c=%c\n", p, c);
        DfsMid(p - 1, c);
      }
    }

    if (p == n - 1 || (p < n - 1 && Dis(high[p], high[p + 1]) == 1)) {
      // printf("has high\n");
      DfsHigh(p - 1);
    }
  }
  void DfsLow(int p, int preZero) {
    // printf("low: p=%d preZero=%d\n", p, preZero);
    if (p == -1) {
      // printf("low is ans\n");
      Update(1);
      return;
    }

    if (preZero || Dis(low[p], low[p + 1]) == 1) {
      // printf("low->low p=%d\n", p);
      DfsLow(p - 1, preZero && (low[p] == '0'));
    }

    for (char c = low[p] + 1; c <= '9'; c++) {
      if (preZero || Dis(c, low[p + 1]) == 1) {
        // printf("low->mid p=%d c=%c\n", p, c);
        DfsMid(p - 1, c);
      }
    }
  }

  void DfsHigh(int p) {
    // printf("high: p=%d\n", p);
    if (p == -1) {
      Update(1);
      return;
    }

    for (char c = '0'; c < high[p]; c++) {
      if (Dis(c, high[p + 1]) == 1) {
        // printf("high->mid p=%d c=%c\n", p, c);
        DfsMid(p - 1, c);
      }
    }

    if (Dis(high[p], high[p + 1]) == 1) {
      // printf("high->high p=%d\n", p);
      DfsHigh(p - 1);
    }
  }

  void DfsMid(int p, char c) {
    int v = c - '0';
    // printf("p=%d c=%c ans=%d\n", p, c, Dfs(v, p));
    Update(Dfs(v, p));
  }

  int Dfs(int v, int p) {
    if (p == -1) return 1;
    if (dp[v][p] != -1) return dp[v][p];
    ll& ret = dp[v][p];

    ret = 0;
    for (int i = 0; i < 10; i++) {
      if (Dis(i, v) == 1) {
        ret = (ret + Dfs(i, p - 1)) % mod;
      }
    }
    return ret;
  }

 public:
  int countSteppingNumbers(string low_, string high_) {
    low = std::move(low_);
    high = std::move(high_);

    dp.resize(10, vector<ll>(111, -1));

    n = max(low.length(), high.length());
    std::reverse(low.begin(), low.end());
    std::reverse(high.begin(), high.end());
    low.resize(n, '0');

    DfsEq(n - 1);

    return ans;
  }
};