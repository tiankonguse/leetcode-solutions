
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
  vector<int> nums(n + 1, 0);
  while (m--) {
    ll v;
    scanf("%lld", &v);
    nums[v]++;
  }

  int firstFlag = 1;
  for (ll i = 1; i <= n; i++) {
    while (nums[i]--) {
      if (firstFlag) {
        firstFlag = 0;
      } else {
        printf(" ");
      }
      printf("%lld", i);
    }
  }
  printf("\n");
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