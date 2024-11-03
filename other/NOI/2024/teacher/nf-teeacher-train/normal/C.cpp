/*
ID: tiankonguse
TASK: C
LANG: C++
*/
#define TASK "C"

#include <bits/stdc++.h>

int debug = 0;
#define myprintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  // freopen(TASK ".in", "r", stdin);
  // freopen(TASK ".out", "w", stdout);
#endif
}

const ll mod = 1000000007;
ll n;
ll K;

const int N = 1e5 + 10;  // 最大 10^5, 至少加1
ll dp[11][N];  // dp[i][b] 前 i 个序列，最后一个是 b 时的答案
ll sums[11];

void Solver() {  //
  scanf("%lld%lld", &n, &K);
  memset(sums, 0, sizeof(sums));  // 初始化

  for (int b = 1; b <= K; b++) {
    dp[0][b] = 1;  // 选择自己
    sums[0] = (sums[0] + dp[0][b]) % mod;
  }

  for (int i = 1; i < n; i++) {
    for (int b = 1; b <= K; b++) {
      ll other = 0;
      for (int a = b * 2; a <= K; a += b) {
        other = (other + dp[i - 1][a]) % mod;  // 不满足 a % b != 0
      }
      dp[i][b] = (sums[i - 1] - other) % mod;
      dp[i][b] = (dp[i][b] + mod) % mod;
      sums[i] = (sums[i] + dp[i][b]) % mod;
    }
  }
  printf("%lld\n", sums[n - 1]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/