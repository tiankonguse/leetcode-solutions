/*
ID: tiankonguse
TASK: comehome
LANG: C++
*/
#define TASK "comehome"

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
vector<vector<pair<ll, ll>>> g(300);
vector<ll> cows(300, 0);
vector<ll> dis(300, inf);
char a[5], b[5];
ll d;

ll Fix(char c) {
  if (c >= 'a' && c <= 'z') {
    return c;
  }
  const ll v = c;
  cows[v] = 1;
  return v;
}

ll minDis = inf;
char ans = 'A';

void UpdateAns(ll v, ll d) {
  if (d < minDis) {
    minDis = d;
    ans = v;
  }
}

template <class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

void Solver(ll from) {
  min_queue<pair<ll, ll>> que;
  dis[from] = 0;
  que.push({0, from});
  while (!que.empty()) {
    auto [d, u] = que.top();
    que.pop();
    if (d != dis[u]) {
      continue;  // 有更优值
    }
    for (auto [v, vd] : g[u]) {
      if (d + vd < dis[v]) {
        dis[v] = d + vd;
        que.push({dis[v], v});
        if (cows[v] == 1) {
          UpdateAns(v, dis[v]);
        }
      }
    }
  }
}

void Solver() {  //
  ll m;
  scanf("%lld", &m);
  while (m--) {
    scanf("%s%s%lld", a, b, &d);
    ll u = Fix(a[0]);
    ll v = Fix(b[0]);
    g[u].push_back({v, d});
    g[v].push_back({u, d});
  }
  Solver('Z');
  printf("%c %lld\n", ans, minDis);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/