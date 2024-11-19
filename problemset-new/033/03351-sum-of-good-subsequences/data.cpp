// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  const int N = 1e5;
  const int V = 1e5;

  int n = rand() % N;
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    printf("%d\n", rand() % V);
  }
  return 0;
}
