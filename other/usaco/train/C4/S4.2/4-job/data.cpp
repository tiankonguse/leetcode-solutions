// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main(int argc, char** argv) {
  int n = atoi(argv[1]);
  printf("%d %d %d\n", n, 2, 2);
  printf("%d %d\n", 2, 3);
  printf("%d %d\n", 2, 3);
  return 0;
}
