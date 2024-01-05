/*
ID: tiankonguse
TASK: dualpal
LANG: C++
*/
#define TASK "dualpal"

#include <bits/stdc++.h>

using namespace std;

bool Check(int v, const int b) {  //
  vector<int> bits;
  while (v) {
    bits.push_back(v % b);
    v /= b;
  }
  int n = bits.size();
  for (int i = 0; i < n; i++) {
    if (bits[i] != bits[n - 1 - i]) {
      return false;
    }
  }
  return true;
}

bool Check(int v) {
  int num = 0;
  for (int i = 2; i <= 10; i++) {
    if (Check(v, i)) {
      num++;
      if (num >= 2) {
        return true;
      }
    }
  }
  return false;
}

void InitIO() {
#ifndef USACO_LOCAL_JUDGE
  freopen(TASK ".in", "r", stdin);
  freopen(TASK ".out", "w", stdout);
#endif
}
void Solver() {  //
  int N, S;
  scanf("%d%d", &N, &S);
  //   printf("begin " TASK "\n");
  while (N > 0) {
    N--;
    while (true) {
      S++;
      if (Check(S)) {
        printf("%d\n", S);
        break;
      }
      //   printf("%d false\n", S);
    }
  }
}

int main() {
  InitIO();
  Solver();
  return 0;
}
