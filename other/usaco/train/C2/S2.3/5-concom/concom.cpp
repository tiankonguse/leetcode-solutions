/*
ID: tiankonguse
TASK: concom
LANG: C++
*/
#define TASK "concom"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

const ll N = 101;
ll n;
vector<vector<ll>> dp;
vector<vector<ll>> base;
void Solver() {  //

  base.resize(N, vector<ll>(N, 0));
  dp.resize(N, vector<ll>(N, 0));
  scanf("%lld", &n);
  queue<tuple<ll, ll, ll>> que;
  while (n--) {
    ll i, j, p;
    scanf("%lld%lld%lld", &i, &j, &p);
    base[i][j] = p;
    que.push({i, j, p});
  }

  while (!que.empty()) {
    auto [a, b, x] = que.front();
    que.pop();
    if (x >= 50) {  // 直接控股
      dp[a][b] = 100;
      // b 的所有控股都是 a 的控股
      for (ll i = 0; i < N; i++) {
        if (dp[b][i] == 100 && dp[a][i] != 100) {
          dp[a][i] = 100;
          que.push({a, i, 100});
        }
      }
    } else {
      if (dp[a][b] != 100) {
        dp[a][b] = x;

        // 新增 a->b， b 可能变成控股公司

      }
    }

    // 对

  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
3
1 2 80
2 3 80
3 1 20

1 2
1 3
2 3
*/