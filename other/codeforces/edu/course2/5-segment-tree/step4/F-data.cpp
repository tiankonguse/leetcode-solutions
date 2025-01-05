// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int N = 20;
const int V = 1000;
int main() {
  srand(time(NULL));
  int n = rand() % N + 1;
  int m = rand() % N + 1;
  printf("%d\n", n);
  const char ops[] = "QI";
  while (m--) {
    int op = m % 2;
    if (op == 1) {
      int l, r, d;
      l = (rand() % n) + 1;
      r = (rand() % n) + 1;
      d = (rand() % V) + 1;
      if (l > r) {
        swap(l, r);
      }
      printf("%c %d %d %d\n", ops[op], l, r, d);
    } else {
      int h;
      h = rand() % V;
      printf("%c %d\n", ops[op], h);
    }
  }
  printf("E\n");
  return 0;
}
