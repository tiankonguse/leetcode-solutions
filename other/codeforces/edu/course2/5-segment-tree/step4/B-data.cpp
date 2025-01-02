// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int N = 100;
const int V = 100;
int main() {
  srand(time(NULL));
  int n = rand() % N;
  int m = rand() % V;
  printf("%d %d \n", n, m);
  while (m--) {
    int op = (rand() % 2) + 1;
    if (op == 1) {
      int l, r, a, d;
      l = (rand() % n) + 1;
      r = (rand() % n) + 1;
      a = (rand() % V) + 1;
      d = (rand() % V) + 1;
      if (l > r) {
        swap(l, r);
      }
      printf("%d %d %d %d %d\n", op, l, r, a, d);
    } else {
      int l;
      l = (rand() % n) + 1;
      printf("%d %d\n", op, l);
    }
  }
  return 0;
}
