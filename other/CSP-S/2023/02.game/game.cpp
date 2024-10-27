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

  // 位置i前面有一个j,能与 j 消除的最短子串位置
  vector<vector<ll>> rights(M, vector<ll>(n + 1, -1));
  for (int i = n - 1; i >= 0; i--) {
    const ll v = str[i] - 'a';
    for (int j = 0; j < M; j++) {
      if (v == j) {
        rights[j][i] = i;
      } else {
        // 自身需要先匹配
        const int k = rights[v][i + 1];
        if (k != -1) {  // 自身匹配了，与下个答案一致
          rights[j][i] = rights[j][k + 1];
        }
      }
    }
  }

  ll ans = 0;
  vector<ll> dp(n + 1, 0);
  dp[n] = 0;
  for (int i = n - 1; i >= 0; i--) {
    const ll v = str[i] - 'a';
    const int k = rights[v][i + 1];
    if (k != -1) {  // 匹配到一个答案
      dp[i] = 1 + dp[k + 1];
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