
/*
ID: tiankonguse
TASK: lock
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7813
*/
#define TASK "lock"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

/*

*/
unordered_map<ll, ll> h;
vector<ll> base = {1, 10, 100, 1000, 10000, 100000};
const int N = 5;
const int M = 9;
ll Flap(const ll num, int i, int j) {
  int v = (num / base[i]) % 10;
  ll V = (v + j) % 10;
  return num - v * base[i] + V * base[i];
}
void SolverOne(const ll num) {
  // 1 个
  for (int i = 0; i < N; i++) {
    for (int j = 1; j <= M; j++) {
      const ll newNum = Flap(num, i, j);
      h[newNum]++;
    }
  }

  // 转动两个
  for (int i = 1; i < N; i++) {
    for (int j = 1; j <= M; j++) {
      const ll newNum = Flap(Flap(num, i - 1, j), i, j);
      h[newNum]++;
    }
  }
}
void Solver() {  //
  ll n;
  scanf("%lld", &n);
  for (ll i = 0; i < n; i++) {
    ll num = 0;
    for (int j = 0; j < N; j++) {
      ll v = 0;
      scanf("%lld", &v);
      num = num * 10 + v;
    }
    SolverOne(num);
  }
  ll ans = 0;
  for (auto [k, v] : h) {
    if (v == n) {
      ans++;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
1
0 0 1 1 5
*/