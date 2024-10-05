
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
递归形式
*/
ll n;
vector<vector<ll>> rights;
ll Dfs(int j, int i) {
  ll& ret = rights[j][i];
  if (ret != -1) {
    return ret;
  }
  if (i == n) {
    return ret = -2;
  }
  const ll v = str[i] - 'a';
  if (v == j) {
    return ret = i;
  }
  const int k = Dfs(v, i + 1);
  if (k != -2) {
    return ret = Dfs(j, k + 1);
  }
  return ret = -2;
}
void Solver() {
  scanf("%lld%s", &n, str);

  // 位置i前面有一个j,能与 j 消除的最短子串位置
  rights.resize(M, vector<ll>(n + 1, -1));

  ll ans = 0;
  vector<ll> dp(n + 1, 0);
  dp[n] = 0;
  for (int i = n - 1; i >= 0; i--) {
    const ll v = str[i] - 'a';
    const int k = Dfs(v, i + 1);
    if (k != -2) {  // 匹配到一个答案
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


babaabab

*/