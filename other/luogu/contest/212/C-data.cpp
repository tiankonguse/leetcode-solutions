// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int N = 100000;
int main() {
  srand(time(NULL));
  int n = (rand() % N) + 1;
  int m = (rand() % N) + 1;
  printf("%d %d\n", n, m);
  for (int i = 0; i < n + m; i++) {
    printf("%d", rand() % 2);
  }
  printf("\n");
  return 0;
}
