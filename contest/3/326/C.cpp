// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<int> dp;
  string kk;
  string s;
  int n;

  int Dfs(int p) {
    if (p < 0) return -1;
    int& ret = dp[p];
    if (ret != n + 1) return ret;

    int len = kk.size();
    for (int i = 1; i < len; i++) {
      int tmp = Dfs(p - i);
      if (tmp != -1) {
        ret = min(ret, tmp + 1);
      }
    }

    if (p >= len) {
      int tmp = Dfs(p - len);
      int l = p - len + 1;
      if (tmp != -1 && strncmp(s.data() + l - 1, kk.data(), len) != 1) {
        ret = min(ret, tmp + 1);
      }
    }

    if (ret == n + 1) {
      ret = -1;
    }
    return ret;
  }

 public:
  int minimumPartition(string s_, int k) {
    s.swap(s_);
    n = s.size();
    dp.resize(n + 1, n + 1);
    kk = to_string(k);
    dp[0] = 0;
    return Dfs(n);
  }
};