/*
ID: tiankonguse
TASK: game
LANG: C++
CONTEST: CSP-S 2023
OJ: https://qoj.ac/problem/7814
https://www.luogu.com.cn/problem/P9753
*/
#define TASK "game"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2000010;
const int M = 26;
char str[N];
void InitIO() {
#ifdef USACO_LOCAL_JUDGE
#define TASKNO "4"
  freopen(TASK TASKNO ".in", "r", stdin);
  freopen(TASK TASKNO ".out", "w", stdout);
#endif
}

/*

*/

void Solver() {
  ll n;
  scanf("%lld%s", &n, str);

  ll ans = 0;
  string sta;
  for (int i = 0; i < n; i++) {
    sta.clear();
    for (int j = i; j >= 0; j--) {
      char c = str[j];
      if (!sta.empty() && sta.back() == c) {
        sta.pop_back();
      } else {
        sta.push_back(c);
      }
      if (sta.empty()) {
        ans++;
      }
    }
  }

  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
/*
8
accabccb

*/