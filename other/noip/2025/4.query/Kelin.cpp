#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int MAXN = 5e4 + 5;

struct MonoQueue {
  int idx[MAXN];
  ll val[MAXN];
  int h, t;

  inline void reset() {
    h = 1;
    t = 0;
  }

  inline void push(ll v, int pos) {
    while (h <= t && val[t] <= v) t--;
    t++;
    idx[t] = pos;
    val[t] = v;
  }

  inline void pop(int limit) {
    while (h <= t && idx[h] < limit) h++;
  }

  inline ll top() { return val[h]; }

  inline bool empty() { return h > t; }

} q1, q2, q3;

int main() {
#ifndef ONLINE_JUDGE
  cin.tie(0)->sync_with_stdio(0);
#endif
  int n;
  cin >> n;
  int m = __lg(n) + 1;
  vector s(n + 1, 0ll);
  vector f(m, vector(n + 1, INT64_MIN)), g(m, vector(n + 1, INT64_MAX));
  f[0][0] = g[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    s[i] += s[i - 1];
    f[0][i] = g[0][i] = s[i];
  }
  for (int j = 1; j <= __lg(n); ++j) {
    int l = 1 << (j - 1);
    for (int i = 0; i + (1 << j) - 1 <= n; ++i) {
      f[j][i] = max(f[j - 1][i], f[j - 1][i + l]);
      g[j][i] = min(g[j - 1][i], g[j - 1][i + l]);
    }
  }
  auto qmax = [&](int l, int r) {
    int j = __lg(r - l + 1);
    return max(f[j][l], f[j][r - (1 << j) + 1]);
  };
  auto qmin = [&](int l, int r) {
    int j = __lg(r - l + 1);
    return min(g[j][l], g[j][r - (1 << j) + 1]);
  };
  int q;
  cin >> q;
  for (int l, r; q--;) {
    cin >> l >> r;
    uint64_t ans = 0;
    q1.reset(), q2.reset(), q3.reset();
    for (int i = 1; i <= n; ++i) {
      ll res = INT64_MIN;
      if (i + l - 1 <= n) {
        ll v1 = s[i + l - 1] - qmin(max(1, i - r + l) - 1, i - 1);
        q1.push(v1, i + l - 1);
      }
      if (i + (r + l) / 2 - 1 <= n) {
        ll v2 = s[i + (r + l) / 2 - 1] - qmin(max(1, i - (r - l + 1) / 2) - 1, i - 1);
        q2.push(v2, i + (r + l) / 2 - 1);
        ll v3 = qmax(i + (r + l) / 2 - 1, min(n, i + r - 1)) - s[i - 1];
        q3.push(v3, i);
      }
      q1.pop(i);
      q2.pop(i + l - 1);
      q3.pop(i - (r - l) / 2);
      if (!q1.empty()) res = max(res, q1.top());
      if (!q2.empty()) res = max(res, q2.top());
      if (!q3.empty()) res = max(res, q3.top());
      if (i + l - 1 <= n) {
        ll v4 = qmax(i + l - 1, min(n, i + (l + r) / 2 - 1)) - qmin(max(1, i - (r - l) / 2) - 1, i - 1);
        res = max(res, v4);
      }
      ans ^= uint64_t(res) * i;
    }
    cout << ans << '\n';
  }
  return 0;
}
