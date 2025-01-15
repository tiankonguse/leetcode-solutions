#include <bits/stdc++.h>
using namespace std;
int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  printf("利用指针变量打印一维数组:\n ");
  int *p = arr;  // p指向arr数组第一个元素（存储第一个元素的地址）
  for (int i = 0; i < 10; i++) {
    if (i != 0) printf(" ");
    printf("%d", *(p + i));
    // printf("%d", p[i]);
  }
  printf("\n");
  printf("利用数组指针打印一维数组:\n ");
  int(*q)[10] = &arr;  // p指向
  for (int i = 0; i < 10; i++) {
    if (i != 0) printf(" ");
    printf("%d", q[0][i]);
  }
  printf("\n");
  return 0;
}



