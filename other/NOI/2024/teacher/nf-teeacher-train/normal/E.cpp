/*
ID: tiankonguse
TASK: E
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

const int N = 1e5 + 10;
char str[N];
ll ans = 0;
ll n;
void Check() {
  ll num = 0;
  for (int i = 0; i < n; i++) {  // 枚举 i 为中心的回文串
    int l = i, r = i;
    while (l >= 0 && r < n && str[l] == str[r]) {
      num++;
      l--,r++;
    }
    l = i, r = i + 1;
    while (l >= 0 && r < n && str[l] == str[r]) {
      num++;
      l--,r++;
    }
  }
  ans = max(ans, num);
}
void Solver() {  //
  scanf("%s", str);
  n = strlen(str);
  for (int i = 0; i < n; i++) {
    const char oldVal = str[i];
    for (char c = 'a'; c <= 'z'; c++) {
      str[i] = c;
      Check();
    }
    str[i] = oldVal;
  }
  printf("%lld\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}

/*
去下厕所
*/