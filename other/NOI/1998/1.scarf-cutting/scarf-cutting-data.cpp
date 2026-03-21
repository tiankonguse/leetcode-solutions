// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  // n: 1<= n <= 100
  int n = rand() % 100 + 1;
  if (n == 1) {
    int m = 0;
    printf("%d\n", n);
    printf("%d\n", m);
    return 0;
  }
  // m: 0 <= m <= n * n - 2
  int m = rand() % (n * n - 1);
  printf("%d\n", n);
  printf("%d\n", m);
  for (int i = 0; i < m; i++) {
    // X: 1<= X <= n
    // Y: 1 <= Y <= 2 * X - 1
    int x = rand() % n + 1;
    int y = rand() % (2 * x - 1) + 1;
    printf("%d %d\n", x, y);
  }
  return 0;
}
