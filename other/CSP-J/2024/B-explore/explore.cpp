/*
ID: tiankonguse
TASK: explore
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11227?contestId=209924
*/
#define TASK "explore"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

char str[1010][1010];
int tick[1010][1010];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

ll ans = 0;
void Add(int x, int y, int T) {
  if (tick[x][y] != T) {
    tick[x][y] = T;
    ans++;
  }
}
void Solver() {  //
  ll t;
  memset(tick, 0, sizeof(tick));
  scanf("%lld", &t);
  for (ll T = 1; T <= t; T++) {
    ll n, m, k;
    ll x, y, d;
    scanf("%lld%lld%lld", &n, &m, &k);
    scanf("%lld%lld%lld", &x, &y, &d);
    ans = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%s", &str[i][1]);
    }
    Add(x, y, T);
    while (k--) {
      int X = x + dir[d][0];
      int Y = y + dir[d][1];
      if (X < 1 || X > n || Y < 1 || Y > m || str[X][Y] != '.') {
        d = (d + 1) % 4;
      } else {
        x = X;
        y = Y;
      }
      Add(x, y, T);
    }
    printf("%lld\n", ans);
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
5 5
*/