/*
ID: tiankonguse
TASK: pow
LANG: C++
https://www.luogu.com.cn/problem/P8813
*/
#define TASK "pow"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
constexpr int INF = 1 << 30;

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using max_queue = priority_queue<T>;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

const ll kMaxVal = 1e9;
ll qpow(ll x, ll v) {
  ll y = 1;
  while (v) {
    if (v & 1) y = y * x;
    v >>= 1;
    x = x * x;
    if (y > kMaxVal) return -1;
    if (v && x > kMaxVal) return -1;
  }
  return y;
}

void Solver() {  //
  ll a, b;
  scanf("%lld%lld", &a, &b);
  printf("%lld\n", qpow(a, b));
}

int main() {
  InitIO();
  Solver();
  return 0;
}
