#include <bits/stdc++.h>
using namespace std;
int main() {
  int arr1[3][5] = {{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}};
  printf("利用指针变量打印二维数组:\n ");
  int *r = arr1;  // p指向arr数组第一个一维数组（存储它的地址）
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (j != 0) printf(" ");
      printf("%d", *((*r + i) + j));
    }
    printf("\n");
  }
  printf("利用数组指针打印二维数组:\n ");
  int(*s)[5] = arr1;  // p指向arr数组第一个一维数组（存储它的地址）
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (j != 0) printf(" ");
      printf("%d", *(*(s + i) + j));
    }
    printf("\n");
  }
  return 0;
}
