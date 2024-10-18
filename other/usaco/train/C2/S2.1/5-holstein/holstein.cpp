/*
ID: tiankonguse
TASK: holstein
LANG: C++
*/
#define TASK "holstein"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n, m;
vector<ll> target;
vector<vector<ll>> g;
vector<ll> buf;
ll ansMask = 0;
ll ansNum = 16;

void UpdateAns(const ll mask, const ll num) {
  printf("");
  if (ansNum > num || (ansNum == num && ansMask < mask)) {
    ansNum = num;
    ansMask = mask;
  }
}

void Dfs(const ll pos, const ll mask, const ll num) {
  if (pos == n) return;

  // 选择
  bool ok = true;
  for (ll i = 0; i < m; i++) {
    buf[i] += g[pos][i];
    if (buf[i] < target[i]) {
      ok = false;
    }
  }
  if (ok) {
    UpdateAns(mask | (1 << (n - pos - 1)), num + 1);
  } else {
    Dfs(pos + 1, mask | (1 << (n - pos - 1)), num + 1);
  }

  for (ll i = 0; i < m; i++) {
    buf[i] -= g[pos][i];
  }

  // 不选择
  Dfs(pos + 1, mask, num);
}

void Solver() {  //
  scanf("%lld", &m);
  target.resize(m);
  for (ll i = 0; i < m; i++) {
    scanf("%lld", &target[i]);
  }
  scanf("%lld", &n);
  g.resize(n, vector<ll>(m));
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      scanf("%lld", &g[i][j]);
    }
  }

  buf.resize(m, 0);
  Dfs(0, 0, 0);

  printf("%lld", ansNum);
  for (ll i = n-1; i >= 0; i--) {
    if (ansMask & (1 << i)) {
      printf(" %lld", n - i);
    }
  }
  printf("\n");
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
      Here are the respective outputs:
        ----- our output ---------
        2_2_3
        ---- your output ---------
        2_3_4
        --------------------------

        ------ Data for Run 3 [length=44 bytes] ------
        4
        1 1 1 1
        4
        1 1 0 0
        1 0 1 0
        0 1 0 1
        0 0 0 1


        ----- our output ---------
        2_6_7
        ---- your output ---------
        2_5_6
        --------------------------

        ------ Data for Run 5 [length=154 bytes] ------
        8 
        10 10 10 10 10 10 10 10 
        7 
        1 1 1 1 1 1 1 1 
        2 2 2 2 2 2 2 2 
        3 3 3 3 3 3 3 3 
        4 4 4 4 4 4 4 4 
        100 100 100 100 100 100 0 0 
        5 5 5 5 5 5 10 0 
        5 5 5 5 5 5 0 10
*/