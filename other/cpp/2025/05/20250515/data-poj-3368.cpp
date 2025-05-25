// 数据生成器
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int getval() {
  int si = (rand() & 1) ? 1 : -1;
  return (rand() % (100001)) * si;
}

const int N = 100001;
int a[N], cnt[N], n, q, k, l, r;

int main() {
  srand(time(NULL));
  int n = rand() % 5000;
  int q = 5000;
  printf("%d %d\n", n, q);
  for (int i = 0; i < n; i++) {
    a[i] = 100000 - (rand() % 200000);
  }
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  while (q--) {
    l = rand() % n + 1;
    r = rand() % n + 1;
    if (l > r) {
      swap(l, r);
    }
    printf("%d %d\n", l, r);
  }
  printf("0\n");

  return 0;
}
