/*
ID: tiankonguse
TASK: bus
LANG: C++
OJ: https://qoj.ac/submission/601150
*/
#define TASK "bus"

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

vector<vector<pair<ll, ll>>> g;  // g[u]{v, a}
min_queue<pair<ll, ll>> que;     // {cost, u}
vector<vector<ll>> dp;


/*
优先队列求最短路，每个节点最多可以到达k次
*/
void Solver() {  //
  ll n, m, k;
  scanf("%lld%lld%lld", &n, &m, &k);
  g.resize(n);
  dp.resize(k, vector<ll>(n, INF));

  while (m--) {
    ll u, v, a;
    scanf("%lld%lld%lld", &u, &v, &a);  // u->v
    u--, v--;                           // 下标转换为从0开始
    g[u].push_back({v, a});
  }

  dp[0][0] = 0;
  que.push({0, 0});

  while (!que.empty()) {
    auto [tu, u] = que.top();
    que.pop();

    // 剪枝，如果有更优解，使用更优解来 bfs
    if (dp[tu % k][u] < tu) {
      tu = dp[tu % k][u];
    }

    for (auto [v, a] : g[u]) {
      ll tv = tu;
      if (tv < a) {  // 道路没开放，在门口等到 num 个 k
        ll num = (a - tv + k - 1) / k;
        tv += num * k;
      }
      tv++;  // 通过这条道路，时间加1

      ll tvk = tv % k;
      if (tv < dp[tvk][v]) {  // 有更优解
        dp[tvk][v] = tv;
        que.push({tv, v});
      }
    }
  }

  if (dp[0][n - 1] == INF) {
    dp[0][n - 1] = -1;
  }
  printf("%lld\n", dp[0][n - 1]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
