/*
ID: tiankonguse
TASK: duel
LANG: C++
CONTEST: CSP-S 2024
OJ: https://www.luogu.com.cn/problem/P11231?contestId=209925
*/
#define TASK "duel"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

ll n;
vector<ll> nums;
void Solver() {  //
  scanf("%lld", &n);
  nums.resize(n, 0);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
  }
  sort(nums.begin(), nums.end());

  int l = 0, r = 1;
  while (r < n) {
    if (nums[r] > nums[l]) {
      l++;
    }
    r++;
  }
  printf("%lld\n", r - l);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5
1 2 3 1 2
2

10
136 136 136 2417 136 136 2417 136 136 136
8

*/