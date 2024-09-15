// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

int debug = 1;
#define myprintf(fmt, args...)      \
  do {                              \
    if (debug) printf(fmt, ##args); \
  } while (0)

typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll NINFL = -INFL;

class Solution {
  vector<vector<ll>> dp;
  vector<int> a;
  vector<int> b;
  int n, m;
  ll Dfs(int n, int m) {
    if (n < 0 || m < 0) return 0;
    ll& ret = dp[n][m];
    if (ret != NINFL) {
      return ret;
    }
    ret = Dfs(n - 1, m - 1) + ll(a[n]) * b[m];
    if (n < m) {
      ret = max(ret, Dfs(n, m - 1));
    }
    return ret;
  }

 public:
  long long maxScore(vector<int>& a_, vector<int>& b_) {
    a.swap(a_);
    b.swap(b_);
    int n = a.size();
    int m = b.size();
    dp.resize(n, vector<ll>(m, NINFL));

    return Dfs(n - 1, m - 1);
  }
};