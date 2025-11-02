// https://www.luogu.com.cn/article/5fe1tbca
#include <bits/stdc++.h>
// #define int long long
// #pragma GCC optimize(3,"Ofast","inline")
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define ll long long
#define bint __int128
#define ull unsigned long long
#define uint unsigned int
#define ld double
#define PII pair<int, int>
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)
#define umap unordered_map
#define rep(k, l, r) for (int k = l; k <= r; ++k)
#define per(k, r, l) for (int k = r; k >= l; --k)
#define cl(f, x) memset(f, x, sizeof(f))
#define pcnt(x) __builtin_popcount(x)
#define lg(x) (31 - __builtin_clz(x))
using namespace std;
void file_IO() {
  freopen("employ.in", "r", stdin);
  freopen("employ.out", "w", stdout);
}
bool M1;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-9;

// 快速幂
ll qpow(ll x, ll v, ll mod) {
  x = x % mod;
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x % mod;
    x = x * x % mod;
    v >>= 1;
  }
  return y;
}

// 模逆元，mod 必须为质数
ll inv(ll x, ll mod) { return qpow(x, mod - 2, mod); }

struct mint {
  const ll mod = 998244353;
  ll x;
  mint(ll x = 0) : x(x) {}
  mint operator+(const mint& b) const { return mint((x + b.x) % mod); }
  mint operator-(const mint& b) const { return mint((x - b.x % mod + mod) % mod); }
  mint operator*(const mint& b) const { return mint((x * b.x) % mod); }
  mint operator*(const ll& b) const { return mint((x * b) % mod); }
  mint operator/(const ll& b) const { return mint((x * inv(b, mod)) % mod); }
  mint operator=(const mint& b) {
    x = b.x;
    return *this;
  }
  mint operator+=(const mint& b) {
    x = (x + b.x) % mod;
    return *this;
  }
  mint operator+=(const ll& b) {
    x = (x + b) % mod;
    return *this;
  }
  mint operator~() const { return mint(qpow(x, mod - 2, mod)); }
};
const int N = 5e2 + 5;
mint jc[N], inv_jc[N];
void init(int n = 5e2) {
  jc[0] = 1;
  rep(i, 1, n) {  //
    jc[i] = jc[i - 1] * i;
  }
  inv_jc[n] = ~jc[n];
  per(i, n - 1, 0) {  //
    inv_jc[i] = inv_jc[i + 1] * (i + 1);
  }
}
mint C(int n, int m) {
  if (m < 0 || n < m) return 0;
  return jc[n] * inv_jc[n - m] * inv_jc[m];
}
mint P(int n, int m) {
  if (m < 0 || n < m) return 0;
  return jc[n] * inv_jc[n - m];
}
int c[N], pre[N];
mint f[N][N][N];
char s[N];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", s + 1);
  rep(i, 1, n) {
    int x;
    scanf("%d", &x);
    ++c[x];
  }
  pre[0] = c[0];
  rep(i, 1, n) pre[i] = pre[i - 1] + c[i];
  f[0][0][0] = 1;
  rep(i, 1, n) {
    rep(j, 0, i - 1) {
      rep(k, 0, i - 1) {
        if (s[i] == 48) {
          rep(t, 0, min(k, c[j + 1])) {
            if (pre[j + 1] >= (i - 1) - (k - t))
              f[i][j + 1][k - t] += f[i - 1][j][k] * C(c[j + 1], t) * P(k, t) * (pre[j + 1] - ((i - 1) - (k - t)));
            f[i][j + 1][k - t + 1] += f[i - 1][j][k] * C(c[j + 1], t) * P(k, t);
          }
        } else {
          rep(t, 0, min(k, c[j + 1])) {
            if (pre[j + 1] >= (i - 1) - k)
              f[i][j + 1][k - t] += f[i - 1][j][k] * C(c[j + 1], t) * P(k, t) * (pre[j] - ((i - 1) - k));
          }
          f[i][j][k + 1] += f[i - 1][j][k];
        }
      }
    }
  }
  mint res = 0;
  rep(j, 0, n - m) res += f[n][j][n - pre[j]] * jc[n - pre[j]];
  printf("%d\n", res.x);
}
bool M2;
// g++ employ.cpp -std=c++14 -Wall -O2 -o employ
signed main() {
  file_IO();
  int testcase = 1;
  init();
  // scanf("%d",&testcase);
  while (testcase--) solve();
  debug("used time = %dms\n", (signed)(1000 * clock() / CLOCKS_PER_SEC));
  debug("used memory = %dMB\n", (signed)((&M1 - &M2) / 1024 / 1024));
  return 0;
}
