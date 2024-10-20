/*
ID: tiankonguse
TASK: hamming
LANG: C++
*/
#define TASK "hamming"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll N, B, D;
vector<vector<ll>> g;
ll MASK;
set<ll> leftMasks;

void Solver() {  //
  scanf("%lld%lld%lld", &N, &B, &D);
  MASK = 1 << B;
  g.resize(MASK);
  for (ll a = 0; a < MASK; a++) {
    leftMasks.insert(a);
    for (ll b = 0; b < MASK; b++) {
      if (__builtin_popcount(a ^ b) < D) {
        g[a].push_back(b);
        g[b].push_back(a);
      }
    }
  }

  ll num = 0;
  while (num < N) {
    num++;
    ll a = *leftMasks.begin();
    printf("%lld%c", a, (num % 10 == 0 || num == N) ? '\n' : ' ');
    for (ll b : g[a]) {
      leftMasks.erase(b);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/