// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  int n;
  int x;
  string s1;
  string s2;
  vector<vector<vector<int>>> dp;
  int Update(int ans, int val) {
    if (ans == INT_MAX) return val;
    if (ans < 0) return val;
    if (val < 0) return ans;
    return min(ans, val);
  }
  int Dfs(int p, int flag, int left) {
    if (p == n) {
      if (flag == 0 && left == 0) {
        return 0;
      } else {
        return INT_MIN;
      }
    }
    if (left >= n) return INT_MIN;

    int& ret = dp[flag][p][left];
    if (ret != INT_MAX) {
      return ret;
    }

    int baseFlag = s1[p] == s2[p];
    // 当前已经相等
    if (flag ^ baseFlag) {
      // 什么都不做
      ret = Update(ret, Dfs(p + 1, 0, left));
    } else {
      if (left > 0) {
        // 直接翻转
        ret = Update(ret, Dfs(p + 1, 0, left - 1));
      }

      // 选择一个 x
      ret = Update(ret, x + Dfs(p + 1, 0, left + 1));

      // 选择一个 1
      ret = Update(ret, 1 + Dfs(p + 1, 1, left));
    }
    return ret;
  }

 public:
  int minOperations(string s1_, string s2_, int x_) {
    x = x_;
    s1.swap(s1_);
    s2.swap(s2_);

    n = s1.size();
    int k = 0;
    for (int i = 0; i < n; i++) {
      if (s1[i] != s2[i]) {
        k++;
      }
    }
    if (k % 2 == 1) {
      return -1;
    }
    if (k == 0) {
      return 0;
    }

    dp.resize(2, vector<vector<int>>(n, vector<int>(n, INT_MAX)));
    return Dfs(0, 0, 0);
  }
};