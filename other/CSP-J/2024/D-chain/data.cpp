// 数据生成器
#include "bits/stdc++.h"
using namespace std;

int main() {
  srand(time(NULL));
  int t = rand() % 5 + 1;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int n = rand() % 1000 + 1;  // 人数
    int k = rand() % 10000 + 1;  // 接龙长度
    int q = rand() % 10000 + 1;  // 查询次数
    printf("%d %d %d\n", n, k, q);

    for (int j = 0; j < n; j++) {
      int l = rand() % 100 + 1;  // 每个人的数字个数
      printf("%d ", l);
      for (int m = 0; m < l; m++) {
        printf("%d ", rand() % 100001 + 1);  // 每个人的数字
      }
      printf("\n");
    }
    for (int j = 0; j < q; j++) {
      int r = rand() % 100 + 1;       // 查询轮次
      int s = rand() % 100001 + 1;  // 查询的值
      printf("%d %d\n", r, s);
    }
  }
  return 0;
}
