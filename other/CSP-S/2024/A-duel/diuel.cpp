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
  multiset<ll> H;
  for (int i = 0; i < n; i++) {
    scanf("%lld", &nums[i]);
    H.insert(nums[i]);
  }
  sort(nums.begin(), nums.end());

  ll ans = n;
  for (int i = 0; i < n; i++) {
    ll v = nums[i];
    auto it = H.lower_bound(v);
    if (it == H.begin()) {
      continue;  // 没有更小值，无法删除
    }
    it--;
    H.erase(it);
    ans--;
  }
  printf("%lld\n", ans);
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