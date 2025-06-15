/*
ID: tiankonguse
TASK: game
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7814
https://www.luogu.com.cn/problem/P9753
*/
#define TASK "game"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2000010;
const int M = 26;
char str[N];
void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

/*

*/

void Solver() {
  ll n;
  scanf("%lld%s", &n, str);

  ll ans = 0;
  vector<ll> dp(n + 1, 0);    //
  vector<ll> next(n + 1, 0);  // [next[i], i] 可消除
  for (int i = 1; i <= n; i++) {
    if (i == 1) continue;  // 一个字符，不可能有答案
    int p = i - 1;
    while (p > 0 && str[i - 1] != str[p - 1]) {
      p = next[p] - 1;
    }
    if (p > 0) {
      dp[i] = 1 + dp[p - 1];
      next[i] = p;
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