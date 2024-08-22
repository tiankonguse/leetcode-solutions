// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;
class Solution {
  vector<vector<int>> dp;
  int n;
  int k;
  vector<int> base;
  int Next(int l, int r, int pre, int v) {
    ll tmp = (v * base[r] + pre) % k;
    if (l != r) {
      tmp = (tmp + v * base[l]) % k;
    }
    return tmp;
  }
  // pos 之前的已经处理，余数为 left
  bool Check(const int l, const int r, const int pre) {
    if (l > r) {
      return pre == 0;
    }
    if (dp[l][pre] == -1) {
      // 43210
      // 00100
      // v * 10^r + v * 10^l + pre
      int V = -2;
      for (int v = 9; v >= 0; v--) {
        ll tmp = Next(l, r, pre, v);
        if (Check(l + 1, r - 1, tmp)) {
          V = v;
          break;
        }
      }
      dp[l][pre] = V;
      //   myprintf("l=%d r=%d pre=%d V=%d\n", l, r, pre, V);
    }
    return dp[l][pre] >= 0;
  }
  void Init() {
    dp.resize(n, vector<int>(10, -1));

    base.resize(n + 1, 0);
    base[0] = 1 % k;
    for (int i = 1; i <= n; i++) {
      base[i] = (base[i - 1] * 10) % k;
    }
  }

 public:
  string largestPalindrome(int n_, int k_) {
    n = n_;
    k = k_;
    Init();
    int l = 0, r = n - 1, pre = 0;
    Check(l, r, pre);

    string ans(n, '0');
    while (l <= r) {
      int v = dp[l][pre];
      //   myprintf("l=%d r=%d pre=%d v=%d\n",l,r,pre,v );
      ans[l] = ans[r] = '0' + v;
      pre = Next(l, r, pre, v);
      l++;
      r--;
    }
    return ans;
  }
};