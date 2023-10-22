// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
class Solution {
  vector<vector<int>> dp, dp2, lr;
  vector<vector<int>> fac;
  string s;
  int Dfs(int n, int k) {
    if (n < k) return -1;
    if (n == 0 && k == 0) return 0;
    if (k == 0) return -1;

    int& ret = dp[n][k];
    if (ret != INT_MAX) return ret;

    for (int i = 1; i <= n; i++) {
      int v1 = Dfs(n - i, k - 1);
      if (v1 == -1) continue;
      int v2 = Dfs2(n - i + 1, n);
      // printf("dfs(%d, %d) i=%d v1=%d v2=%d\n", n, k, i, v1, v2);
      if (v1 >= 0 && v2 >= 0) {
        ret = min(ret, v1 + v2);
      }
    }
    if (ret == INT_MAX) {
      ret = -1;
    }
    return ret;
  }

  int Dfs2(int l, int r) {  // [1,n]
    int& ret = dp2[l][r];
    if (ret != INT_MAX) return ret;
    int len = r - l + 1;
    // printf("l=%d r=%d len=%d\n", l, r, len);
    for (auto d : fac[len]) {
      int v = Solver(l, r, d);
      // printf("fac d=%d v=%d\n", d, v);
      ret = min(ret, v);
    }
    if (ret == INT_MAX) {
      ret = -1;
    }
    return ret;
  }

  int Solver(int l, int r, int d) {  // [1,n]
    int ans = 0;
    int len = r - l + 1;
    for (int i = 0; i < d; i++) {
      int L = i;
      int R = len / d * d + i;
      if (R >= len) {
        R -= d;
      }
      for (; L < R; L += d, R -= d) {
        if (s[l + L - 1] != s[l + R - 1]) {
          ans++;
        }
      }
    }
    return ans;
  }

 public:
  int minimumChanges(string s_, int k) {
    s.swap(s_);
    int n = s.size();
    fac.resize(n + 1);

    for (int i = 1; i <= n; i++) {
      for (int k = 1; k < i; k++) {
        if (i % k == 0) {
          fac[i].push_back(k);
        }
      }
    }

    dp.resize(n + 1, vector<int>(n + 1, INT_MAX));
    dp2.resize(n + 1, vector<int>(n + 1, INT_MAX));

    return Dfs(n, k);
  }
};

int main() {
  int ans = 2;
  string s = "edaswf";
  int k = 1;
  TEST_SMP2(Solution, minimumChanges, ans, s, k);

  return 0;
}
