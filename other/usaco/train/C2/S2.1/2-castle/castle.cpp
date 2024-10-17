/*
ID: tiankonguse
TASK: castle
LANG: C++
*/
#define TASK "castle"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

// 朴素并查集
// 参考资料：https://oi-wiki.org/ds/dsu/
// 树上并查集每个子树需要维护一个集合，保证大集合向小集合合并，并引用返回大集合就不会超时了

class Dsu {
  vector<int> fa, score;

 public:
  void Init(int n) {
    fa.resize(n);
    score.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i, score[i] = 0;
    }
  }

  int Find(int x) {
    if (fa[x] != x) {
      fa[x] = Find(fa[x]);
    }
    return fa[x];
  }

  // Union，也成为了 Merge
  void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      if (score[x] > score[y]) {
        fa[y] = x;
      } else {
        fa[x] = y;
        if (score[x] == score[y]) {
          ++score[y];
        }
      }
    }
  }
  void AddScore(int x) {
    x = Find(x);
    score[x]++;
  }

  int GetScore(int x) {
    x = Find(x);
    return score[x];
  }
};
int dir4[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

ll n, m;
ll grid[55][55];
Dsu dsu;
vector<ll> flag;
ll nm;
const string WNES = "WNES";

void Solver() {  //
  scanf("%lld%lld", &m, &n);
  nm = n * m;
  dsu.Init(nm);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%lld", &grid[i][j]);
      const ll a = i * m + j;
      for (int k = 0; k < 4; k++) {
        if (grid[i][j] & (1 << k)) continue;
        const ll x = i + dir4[k][0];
        const ll y = j + dir4[k][1];
        const ll b = x * m + y;
        dsu.Union(a, b);
      }
    }
  }

  flag.resize(nm, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      const ll a = i * m + j;
      flag[dsu.Find(a)]++;
    }
  }

  ll roomNum = 0;
  ll maxRoom = 0;
  ll removeMax = 0;
  ll removeX = 0, removeY = 0, dir = 0;
  tuple<ll, ll, ll, ll> ans = {removeMax, -removeY, removeX, -dir};

  for (int i = 0; i < nm; i++) {
    if (flag[i]) {
      roomNum++;
      maxRoom = max(maxRoom, flag[i]);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      const ll a = i * m + j;
      // UP north 1
      // RIGHT ease 2
      for (int k = 1; k <= 2; k++) {
        if (grid[i][j] & (1 << k)) {  // 有墙
          const ll x = i + dir4[k][0];
          const ll y = j + dir4[k][1];
          if (x < 0 || y >= m) continue;
          const ll b = x * m + y;
          const ll fa = dsu.Find(a);
          const ll fb = dsu.Find(b);
          if (fa == fb) continue;
          const ll ab = flag[fa] + flag[fb];
          const tuple<ll, ll, ll, ll> tmp = {ab, -j, i, -k};

          if (tmp > ans) {
            ans = tmp;
            removeMax = ab;
            removeX = i;
            removeY = j;
            dir = k;
          }
        }
      }
    }
  }

  printf("%lld\n", roomNum);
  printf("%lld\n", maxRoom);
  printf("%lld\n", removeMax);
  printf("%lld %lld %c\n", removeX + 1, removeY + 1, WNES[dir]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
