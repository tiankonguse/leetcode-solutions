/*
ID: tiankonguse
TASK: crypt1
LANG: C++
*/
#define TASK "crypt1"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
unordered_set<int> h;

int ans = 0;

bool Check(int v) {
  while (v) {
    if (h.count(v % 10) == 0) return false;
    v /= 10;
  }
  return true;
}
void Dfs(const int p, const int a = 0, const int b = 0) {
  if (p == 5) {
    if (Check(a * b)) {
    //   printf("a=%d b=%d a*b=%d a*b0=%d a*b1=%d\n", a, b, a * b, a * (b / 10),
    //          a * (b % 10));
      ans++;
    }
    return;
  }

  for (auto v : h) {
    if (p < 3) {
      if (p == 0 && v == 0) continue;  // a 不能有前缀 0
      Dfs(p + 1, a * 10 + v, b);
    } else {
      if (p == 3 && v == 0) continue;  // b 不能有前缀 0
      if (a * v > 999 || !Check(a * v)) continue;
      Dfs(p + 1, a, b * 10 + v);
    }
  }
}

void Solver() {  //
  int n;
  scanf("%d", &n);

  h.clear();
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    h.insert(v);
  }
  Dfs(0);
  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
