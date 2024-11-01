/*
ID: tiankonguse
TASK: A
LANG: C++
*/
#define TASK "A"

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

ll n;
vector<ll> nums;
ll ans = 0;

void Solver() {  //
  n = 8;
  nums.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  sort(nums.begin(), nums.end());
  for (int i = 3; i < nums.size(); i++) {
    ans += nums[i];
  }
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*

*/