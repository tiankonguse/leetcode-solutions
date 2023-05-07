// #include <bits/stdc++.h>

#include "base.h"
using namespace std;

typedef long long ll;

class Solution {
 public:
  int n, m, mod;
  int a[9], b[9];
  int sd[1 << 9], pw[200], ipw[200];
  map<int, int> f[1 << 9];

  int power(int a, int n) {
    int tp = 1;
    while (n) {
      if (n & 1) {
        tp = 1ll * tp * a % mod;
      }
      a = 1ll * a * a % mod, n >>= 1;
    }
    return tp;
  }

  int ct(int s) { return sd[s] + 2 * (2 * __builtin_popcount(s) - 1); }

  int dfs(int s, int target) {
    if (__builtin_popcount(s) <= m) {
      auto it = f[s].find(target);
      if (it != f[s].end()) {
        return it->second;
      }
      return 0;
    }

    target = (target + mod - 9) % mod;
    target = (target + mod - pw[ct(s) - 1]) % mod;
    target = 1ll * target * ipw[1] % mod;
    if (target < 0) {
      target += mod;
    }

    int ans = 0;
    for (int t = s & (s - 1); t; t = (t - 1) & s) {
      int k = s ^ t;
      if (__builtin_popcount(t) < __builtin_popcount(k)) {
        for (auto [x, v] : f[t]) {
          ans += v * dfs(k, (target + 1ll * (mod - x) * pw[ct(k)]) % mod);
        }
      } else {
        for (auto [x, v] : f[k]) {
          ans += v * dfs(t, 1ll * (target + mod - x) * ipw[ct(k)] % mod);
        }
      }
    }

    return ans;
  }

  int treeOfInfiniteSouls(vector<int>& gem, int p, int target) {
    n = gem.size(), m = (n + 1) / 2;
    if (p == 2 || p == 5) {
      if (p == 2) {
        if (target != 1) {
          return 0;
        }
      }

      if (p == 5) {
        if (target != 4) {
          return 0;
        }
      }

      int f[10], c[10][10];
      for (int i = 0; i <= n; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
          c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
      }

      f[1] = 1;
      for (int i = 2; i <= n; i++) {
        f[i] = 0;
        for (int j = 1; j < i; j++) {
          f[i] += f[j] * f[i - j] * c[i][j];
        }
      }
      return f[n];
    }
    mod = p;
    for (int i = 0; i != n; i++) {
      a[i] = gem[i];
      int x = a[i];
      b[i] = 1;
      while (x >= 10) {
        x /= 10, b[i]++;
      }
    }

    pw[0] = ipw[0] = 1;
    for (int i = 1, x = power(10, mod - 2); i != 200; i++) {
      pw[i] = 1ll * pw[i - 1] * 10 % mod;
      ipw[i] = 1ll * ipw[i - 1] * x % mod;
    }

    for (int i = 1; i != (1 << n); i++) {
      int x = __lg(i);
      sd[i] = sd[i ^ (1 << x)] + b[x];
    }

    for (int s = 1; s != (1 << n); s++) {
      if (__builtin_popcount(s) > m) {
        continue;
      }

      if (__builtin_popcount(s) == 1) {
        int x = __lg(s);
        f[s][(pw[b[x] + 1] + 9 + 10ll * a[x]) % mod] = 1;
        continue;
      }

      for (int t = s & (s - 1); t; t = (t - 1) & s) {
        int k = s ^ t;
        for (auto [v1, x1] : f[t]) {
          for (auto [v2, x2] : f[k]) {
            int v = (1ll * v1 * pw[ct(k) + 1] + 10ll * v2 + 9 + pw[ct(s) - 1]) %
                    mod;
            f[s][v] += x1 * x2;
          }
        }
      }
    }

    return dfs((1 << n) - 1, target);
  }
};