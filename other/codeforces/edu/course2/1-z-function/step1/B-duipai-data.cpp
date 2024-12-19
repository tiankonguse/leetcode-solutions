// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int N = 500;
char str[N];
int main() {
  srand(time(NULL));
  int n = (rand() % N )+ 1;
  str[n] = '\0';
  for (int i = 0; i < n; i++) {
    str[i] = 'a' + (rand() % 26);
  }
  printf("1\n");
  printf("%s\n", str);
  return 0;
}
