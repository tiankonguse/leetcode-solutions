/*
ID: tiankonguse
TASK: agrinet
LANG: C++
*/
#define TASK "agrinet"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 60;
constexpr ll MOD = 1000000007;

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<vector<ll>> g;

ll Prime(ll u) {
  vector<ll> flag(n, 0);
  ll ans = 0;
  flag[u] = 1;
  g[u][u] = inf;
  for (ll i = 1; i < n; i++) {
    ll v = u;
    for (int j = 0; j < n; j++) {
      if (flag[j]) continue;
      if (g[u][j] < g[u][v]) {
        v = j;
      }
    }
    ans += g[u][v];
    flag[v] = 1;
    for (ll j = 0; j < n; j++) {
      if (flag[j]) continue;
      g[u][j] = min(g[u][j], g[v][j]);
    }
  }

  return ans;
}

void Solver() {  //
  scanf("%lld", &n);
  g.resize(n, vector<ll>(n, 0));
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      scanf("%lld", &g[i][j]);
    }
  }
  printf("%lld\n", Prime(0));
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/