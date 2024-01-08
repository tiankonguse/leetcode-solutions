/*
ID: tiankonguse
TASK: combo
LANG: C++
*/
#define TASK "combo"

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
int n;
unordered_set<int> h;

void Check(int a, int b, int c) {
  for (int i = -2; i <= 2; i++) {
    for (int j = -2; j <= 2; j++) {
      for (int k = -2; k <= 2; k++) {
        int A = (a + i + n) % n;
        int B = (b + j + n) % n;
        int C = (c + k + n) % n;
        h.insert(A * 100 * 100 + B * 100 + C);
      }
    }
  }
}

void Solver() {  //
  scanf("%d", &n);

  h.clear();
  for (int i = 0; i < 2; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a--, b--, c--;
    Check(a, b, c);
  }
  int ans = h.size();
  printf("%d\n", ans);
}

int main() {
  InitIO();
  Solver();
  return 0;
}
