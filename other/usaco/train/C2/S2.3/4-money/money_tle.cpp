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
vector<vector<ll>> dp;

ll Dfs(const ll p, const ll v) {
  if (v == 0) return 1;
  if (p == -1) return 0;
  ll& ret = dp[p][v];
  if (ret != -1) return ret;
  ret = 0;
  for (ll i = 0; i <= v; i += nums[p]) {
    ret += Dfs(p - 1, v - i);
  }
//   printf("p=%lld v=%lld ret=%lld\n", p, v, ret);
  return ret;
}
void Solver() {  //
  scanf("%lld%lld", &N, &V);
  nums.resize(N);
  for (int i = 0; i < N; i++) {
    scanf("%lld", &nums[i]);
  }
  dp.resize(N, vector<ll>(V + 1, -1));
  printf("%lld\n", Dfs(N - 1, V));
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