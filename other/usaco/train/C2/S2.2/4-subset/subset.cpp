/*
ID: tiankonguse
TASK: subset
LANG: C++
*/
#define TASK "subset"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll n;
vector<vector<ll>> dp;

ll Dfs(const ll n, const ll sum) {
  if (sum == 0) return 1;  // 前面的都不需要选择
  if (n == -1) return 0;   // 没答案

  ll& ret = dp[n][sum];
  if (ret != -1) return ret;
  ret = 0;

  const ll v = n + 1;
  // 选择
  if (v <= sum) {
    ret += Dfs(n - 1, sum - v);
  }

  // 不选择
  ret += Dfs(n - 1, sum);

  return ret;
}

void Solver() {  //
  scanf("%lld", &n);
  ll sum = (1 + n) * n / 2;
  if (sum % 2 == 1) {
    printf("0\n");
    return;
  }

  dp.resize(n, vector<ll>(sum / 2 + 1, -1));
  printf("%lld\n", Dfs(n - 1, sum / 2) / 2);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
Test 1: TEST OK [0.004 secs limit:1s, 1636 KB]
Test 2: TEST OK [0.004 secs limit:1s, 1624 KB]
Test 3: TEST OK [0.004 secs limit:1s, 1708 KB]
Test 4: TEST OK [0.004 secs limit:1s, 1704 KB]
Test 5: TEST OK [0.004 secs limit:1s, 1708 KB]
Test 6: TEST OK [0.004 secs limit:1s, 3380 KB]
Test 7: TEST OK [0.004 secs limit:1s, 1684 KB]
*/