/*
ID: tiankonguse
TASK: poker
LANG: C++
CONTEST: CSP-J 2024
OJ: https://www.luogu.com.cn/problem/P11227?contestId=209924
*/
#define TASK "poker"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
  // #ifndef USACO_LOCAL_JUDGE
  //   freopen(TASK ".in", "r", stdin);
  //   freopen(TASK ".out", "w", stdout);
  // #endif
}

unordered_set<string> H;
char str[4];
void Solver() {  //
  ll n;
  scanf("%lld", &n);
  while (n--) {
    scanf("%s", str);
    H.insert(str);
  }
  ll ans = 52 - H.size();
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
5 5
*/