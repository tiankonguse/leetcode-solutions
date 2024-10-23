/*
ID: tiankonguse
TASK: money
LANG: C++
*/
#define TASK "money"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
ll V, N;
vector<ll> nums;
vector<ll> dp;

void Solver() {  //
  scanf("%lld%lld", &N, &V);
  nums.resize(N);
  for (int i = 0; i < N; i++) {
    scanf("%lld", &nums[i]);
  }
  dp.resize(V + 1, 0);

  dp[0] = 1;
  for (int i = 0; i < N; i++) {
    for (int v = 0; v < V; v++) {
      ll tmp = v + nums[i];
      if (tmp <= V) {
        dp[tmp] += dp[v];
      }
    }
  }

  printf("%lld\n", dp[V]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
8 10000
1 2 3 4 5 6 20 25
*/