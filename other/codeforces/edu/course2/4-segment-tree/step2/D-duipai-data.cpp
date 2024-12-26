// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

// const int N = 100000;
// const int M = 100000;
// const int V = 1e9;
const int N = 10;
const int M = 10;
const int V = 1e1;

inline int Rand(int l, int r) {  // [l, r]
  int len = r - l + 1;
  return rand() % len + l;
}

int main() {
  srand(time(NULL));
  int n = Rand(1, N);
  int m = Rand(1, N);
  printf("%d %d\n", n, m);

  for (int i = 0; i < n; i++) {
    int v = Rand(0, V);
    printf("%d ", v);
  }
  printf("\n");
  for (int i = 0; i < m; i++) {
    int op = Rand(1, 2);
    if (op == 1) {
      int i = Rand(0, n - 1);
      int v = Rand(0, V);
      printf("%d %d %d\n", op, i, v);
    } else {
      int x = Rand(0, V);
      int l = Rand(0, n - 1);
      printf("%d %d %d\n", op, x, l);
    }
  }
  return 0;
}
