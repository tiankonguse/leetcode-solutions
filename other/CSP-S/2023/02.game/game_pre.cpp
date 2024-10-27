/*
ID: tiankonguse
TASK: game
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7814
*/
#define TASK "game"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2000010;
const int M = 26;
char str[N];
void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

/*

*/

void Solver() {
  ll n;
  scanf("%lld%s", &n, str);

  ll ans = 0;
  vector<ll> dp(n + 1, 0);
  vector<ll> nexts(n + 1, n);
  for (int i = n - 1; i >= 0; i--) {
    int j = i + 1;
    while (j < n && str[i] != str[j]) {
      j = nexts[j] + 1; // 复杂度 O(26 N)
    }
    if (j < n) {
      nexts[i] = j;
      dp[i] = 1 + dp[j + 1];
      ans += dp[i];
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
8
accabccb

*/