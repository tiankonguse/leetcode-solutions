/*
ID: tiankonguse
TASK: numtri
LANG: C++
*/
#define TASK "numtri"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}

ll nums[1010][1010];
void Solver() {  //
  ll n;
  scanf("%lld", &n);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j <= i; j++) {
      scanf("%lld", &nums[i][j]);
    }
  }

  for (ll i = n - 2; i >= 0; i--) {
    for (ll j = 0; j <= i; j++) {
      nums[i][j] += max(nums[i + 1][j], nums[i + 1][j + 1]);
    }
  }
  printf("%lld\n", nums[0][0]);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
