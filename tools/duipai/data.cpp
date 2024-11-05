// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  int a = rand() % 10000;
  int b = rand() % 10000;
  printf("%d %d \n", a, b);
  return 0;
}
