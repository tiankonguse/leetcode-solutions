// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  int n = rand() % 10 + 1;
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    printf("%d ", rand() % 2);
  }
  printf("\n");
  for (int i = 2; i <= n; i++) {
    printf("%d %d\n", i, rand() % (i - 1) + 1);
  }
  return 0;
}
