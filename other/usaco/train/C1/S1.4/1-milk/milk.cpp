/*
ID: tiankonguse
TASK: milk
LANG: C++
*/
#define TASK "milk"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
void Solver() {  //
  int N, M;
  scanf("%d%d", &N, &M);
  vector<pair<ll, ll>> nums;
  nums.reserve(M);
  for (int i = 0; i < M; i++) {
    ll P, A;
    scanf("%lld %lld", &P, &A);
    nums.push_back({P, A});
  }
  sort(nums.begin(), nums.end());
  ll ans = 0;
  for (auto [P, A] : nums) {
    // printf("P=%lld A=%lld N=%d\n", P, A, N);
    if (A <= N) {
      ans += P * A;
      N -= A;
    } else {
      ans += P * N;
      N -= N;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
