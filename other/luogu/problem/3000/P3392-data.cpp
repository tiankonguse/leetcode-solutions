// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int MAX_N = 50;
const int MIN_N = 3;
string s = "WRB";
int main() {
  srand(time(NULL));
  int n = (rand() % (MAX_N - MIN_N + 1)) + MIN_N;
  int m = (rand() % MAX_N) + 1;
  printf("%d %d \n", n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%c", s[rand() % 3]);
    }
    printf("\n");
  }
  return 0;
}
