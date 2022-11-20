#include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
  vector<vector<ll>> dp;
  vector<int> pre;
  string s;
  vector<int> h = {0, 0, 1, 3, 0, 5, 0, 7, 0, 0, 0};
  int minLength;
  ll Dfs(int n, int k) {
    if (n == 0 && k == 0) return 1;
    if (n < 0 || k < 0) return 0;

    ll& ret = dp[n][k];
    if (ret != -1) return ret;

    ret = 0;

    if (k * minLength < n) {
      return ret = 0;
    }

    if (h[s[n - 1]]) {
      return ret = 0;
    }

    int pos = pre[n];
    while (pos != -1) {
      if (n - pos + 1 >= minLength) {
        ret = (ret + Dfs(pos - 1, k - 1)) % 1000000007;
      }
      pos = pre[pos];
    }

    printf("n=%d k=%d ret=%lld\n", n, k);
    return ret;
  }

 public:
  int beautifulPartitions(string s_, int k, int minLength_) {
    minLength = minLength_;
    s.swap(s_);

    int n = s.size();

    pre.resize(n + 2, -1);
    int pos = 1;
    for (int i = 2; i <= n; i++) {
      pre[i] = pos;
      if (h[s[i - 1] - '0']) {
        pos = i;
      }
    }

    dp.resize(n + 2, vector<ll>(k + 2, -1));
    return Dfs(n, k);
  }
};