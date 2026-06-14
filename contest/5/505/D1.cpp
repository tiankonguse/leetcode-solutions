#include <bits/stdc++.h>

using i64 = long long;

struct segtree {
  int n;
  std::vector<std::pair<i64, i64>> t;
  segtree(int n) : n(n) { t.assign(n << 1, {i64(-1e18), i64(-1e18)}); }
  void set(int i, std::pair<i64, i64> x) {
    for (t[i += n] = x; i > 1; i >>= 1) t[i >> 1] = std::max(t[i], t[i ^ 1]);
  }
  std::pair<i64, i64> prod(int l, int r) {
    std::pair<i64, i64> x = {i64(-1e18), i64(-1e18)};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) x = std::max(x, t[l++]);
      if (r & 1) x = std::max(x, t[--r]);
    }
    return x;
  }
};

class Solution {
 public:
  long long maximumSum(std::vector<int>& a, int m, int l, int r) {
    using i64 = long long;
    int n = a.size();

    std::vector<i64> p(n + 1);
    for (int i = 0; i < n; i++) p[i + 1] = p[i] + a[i];

    auto work = [&](i64 k) -> std::pair<i64, i64> {
      std::vector<std::pair<i64, i64>> f(n + 1, {i64(-1e18), i64(-1e18)});
      segtree seg(n + 1);
      seg.set(0, {0, 0});
      for (int i = 1; i <= n; i++) {
        int lb = i - r, rb = i - l + 1;
        lb = std::max(lb, 0);
        rb = std::max(rb, 0);
        auto s = seg.prod(lb, rb);
        s.first += p[i] - k;
        s.second++;
        s = std::max(s, f[i - 1]);
        f[i] = s;
        s = std::max(s, {0, 0});
        s.first -= p[i];
        seg.set(i, s);
      }
      return f[n];
    };
    auto [sum, cnt] = work(0);
    if (cnt <= m) return sum;

    i64 left = -2e13, right = 2e13;
    i64 ans = 0;
    while (left <= right) {
      i64 mid = (left + right) / 2;
      auto [sum, cnt] = work(mid);
      if (cnt >= m) {
        ans = sum + mid * m;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return ans;
  }
};