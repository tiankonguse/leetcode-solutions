
/*
ID: tiankonguse
TASK: tree
LANG: C++
CONTEST: CSP-S 2023
qoj: https://qoj.ac/contest/1428/problem/7816
luogu: https://www.luogu.com.cn/problem/P9755
*/
#define TASK "tree3"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll debug = 0;
#define myprintf(...)                        \
  do {                                       \
    if (debug) fprintf(stdout, __VA_ARGS__); \
  } while (0)

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
  // #endif
}
ll rd() {
  ll x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  }
  return x * w;
}

vector<tuple<ll, ll, ll>> points;
vector<vector<ll>> g;
ll n;

vector<ll> lastDay;

/*
h=max(b+xc,1)
ci<0: b-c, b-2c, b-3c, ...,     1
ci=0:   b,    b,    b, ...,     b
ci>0: b+c, b+2c, b+3c, ..., b+k*c

b+xc >= 1
b - 1 >= -cx
(b - 1) / (-c) >= x

*/
bool FixRangeSum(const ll i, const ll x0, const ll xn, ll A) {
  const auto [a, b, c] = points[i];
  const ll down = xn - x0 + 1;
  const ll low = min(x0 * c + b, xn * c + b);
  const ll high = max(x0 * c + b, xn * c + b);
  if (i == 0) {
    // printf(
    //     "fix: i[%lld] x0[%lld] xn[%lld] A[%lld] down[%lld] low[%lld] "
    //     "high[%lld] A/down[%lld]\n",
    //     i, x0, xn, A, down, low, high, A / down);
  }
  if (A / down < low) {  //
    return true;
  }
  A -= low * down;

  return (high - low) * down / 2 >= A;
}
bool CheckRangeSum(const ll i, const ll x0, const ll xn) {
  const auto [a, b, c] = points[i];
  ll A = a;
  if (c >= 0) {
    return FixRangeSum(i, x0, xn, a);
  }
  // c < 0
  const ll one = (b - 1) / (-c);
  // if (i == 58099) {
  //   myprintf("i[%lld] one[%lld]\n", i, one);
  // }
  if (x0 > one) {  // 全是 1
    return xn - x0 + 1 >= A;
  } else if (xn <= one) {  // 斜线
    return FixRangeSum(i, x0, xn, a);
  } else {  // 一半斜线 + 一半 1
    if (xn - one >= A) {
      return true;
    }
    return FixRangeSum(i, x0, one, a - (xn - one));
  }
}
ll Cal(const ll i, const ll d) {  //
  // [1, x] [x, d]
  // const auto [a, b, c] = points[i];
  ll l = 1, r = d + 1;
  while (l < r) {                // [l, r)
    const ll mid = (l + r) / 2;  // sum(mid, d)
    if (CheckRangeSum(i, mid, d)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  if (r == 1) {  // 不满足要求
    // myprintf("Cal: i[%lld] a[%lld] b[%lld] c[%lld] d[%lld]\n", i, a, b, c,
    // d);
    return -1;
  }
  return r - 1;
}

bool Dfs(const ll u, const ll maxDay, const ll pre = -1) {
  lastDay[u] = Cal(u, maxDay);
  if (lastDay[u] < 1) {
    // myprintf("Dfs u[%lld] lastDay[%lld]\n", u, lastDay[u]);
    return false;
  }
  for (auto v : g[u]) {
    if (v == pre) continue;
    if (!Dfs(v, maxDay, u)) {
      return false;
    }
    lastDay[u] = min(lastDay[u], lastDay[v] - 1);
    if (lastDay[u] < 1) {
      // myprintf("Dfs pre: u[%lld] lastDay[%lld] v[%lld] lastDay[%lld]\n", u,
      //          lastDay[u], v, lastDay[v]);
      return false;
    }
  }
  return true;
}
bool Check(ll maxDay) {
  if (!Dfs(0, maxDay)) {
    // myprintf("dfs err: maxDay[%lld]\n", maxDay);
    return false;
  }
  sort(lastDay.begin(), lastDay.end());
  for (ll i = 1; i <= n; i++) {
    if (lastDay[i - 1] < i) {
      // myprintf("sort err: i[%lld] > lastDay[%lld]\n", i, lastDay[i - 1]);
      return false;
    }
  }
  return true;
}
void Solver() {  //
  scanf("%lld", &n);
  points.reserve(n);
  lastDay.resize(n);
  g.resize(n);
  for (ll i = 0; i < n; i++) {
    ll a, b, c;
    a = rd();
    b = rd();
    c = rd();
    // scanf("%lld%lld%lld", &a, &b, &c);
    points.push_back({a, b, c});
  }
  for (ll i = 1; i < n; i++) {
    ll u, v;
    u = rd();
    v = rd();
    // scanf("%lld%lld", &u, &v);
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ll l = 1, r = 10e9 + 1;
  while (l < r) {  //[l,r)
    ll mid = (l + r) / 2;
    if (Check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld\n", r);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
4
12 1 1
2 4 -1
10 3 0
7 10 -2
1 2
1 3
3 4

5




*/