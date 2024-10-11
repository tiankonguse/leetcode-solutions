
/*
ID: tiankonguse
TASK: survey
LANG: C++
CONTEST: 2021 年 CCF NOI线上教师培训测试
OJ:
*/
#define TASK "survey"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

void Solver() {  //
  ll n, m;
  scanf("%lld%lld", &n, &m);
  vector<int> nums(m, 0);
  nums.reserve(m);
  for (ll i = 0; i < m; i++) {
    scanf("%lld", &nums[i]);
  }

  sort(nums.begin(), nums.end());
  for (ll i = 0; i < nums.size(); i++) {
    printf("%lld%c", nums[i], i + 1 == nums.size() ? '\n' : ' ');
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
5 10
2 5 2 2 5 2 2 2 1 2
*/