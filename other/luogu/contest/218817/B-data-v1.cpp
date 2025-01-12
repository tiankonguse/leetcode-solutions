// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  int n = 5;
  printf("5\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", rand() % 2);
  }
  printf("\n");
  for (int i = 2; i <= 5; i++) {
    printf("1 %d\n", i);
  }
  return 0;
}
