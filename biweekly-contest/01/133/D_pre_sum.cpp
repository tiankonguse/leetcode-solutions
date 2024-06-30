// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;

class Solution {
  vector<vector<ll>> dp;
  unordered_map<int, int> h;
  ll Solver(int N, int X) {  //
    dp[0][0] = 1;

    for (int n = 1; n <= N; n++) {
      for (int x = 0; x <= X; x++) {
        if (h.count(n) && h[n] != x) {
          continue;
        }
        for (int i = max(x - n + 1, 0); i <= x; i++) {
          dp[n][x] = (dp[n][x] + dp[n - 1][i]) % mod;
        }
      }
    }

    return dp[N][X];
  }

 public:
  int numberOfPermutations(int n, vector<vector<int>>& requirements) {
    int m = requirements.size();
    sort(requirements.begin(), requirements.end());
    for (int i = 1; i < m; i++) {
      int endi = requirements[i][0];
      int cnti = requirements[i][1];

      if (cnti < requirements[i - 1][1]) return 0;  // 单调性不合法，不存在
      if (n * (n + 1 / 2) < cnti) return 0;  // 参数不合法，不存在
    }
    for (auto& r : requirements) {
      h[r[0] + 1] = r[1];
    }

    int endVal = requirements[m - 1][1];

    // 题意保障最后一个一定是 n, 这里不做这个假设
    int N = n * n;
    dp.resize(n + 1, vector<ll>(N + 1, 0));
    return Solver(n, endVal);
  }
};