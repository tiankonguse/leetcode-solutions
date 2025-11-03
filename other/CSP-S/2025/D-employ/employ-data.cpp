// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

int main() {
  srand(time(NULL));
  int n = rand() % 3 + 1; // [1,3]
  int m = rand() % (n + 1);  // [0, n]
  printf("%d %d \n", n, m);
  string s(n, '1');
  printf("%s\n", s.c_str());
  for (int i = 1; i <= n; i++) {  // [0, n]
    int c = rand() % (n + 1);
    printf("%d ", c);
  }
  printf("\n");
  return 0;
}
