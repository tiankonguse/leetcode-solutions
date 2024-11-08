#include <bits/stdc++.h>
using namespace std;
void QuickSort(int a[], const int left, const int right) {
  int l = left;   // 左边
  int r = right;  // 右边
  if (l >= r) return;
  while (l < r) {
    while (l < r && a[l] <= a[left])  // 从左边找第一个比关键字大的数
      l++;
    while (l < r && a[r] > a[left])  // 从左边找第一个比关键字小的数，
      r--;
    swap(a[l], a[r]);  // 交换两个数字的位置
  }
  l--;                  // 在循环体里面i会加1
  swap(a[left], a[l]);  // 交换关键字和最终位置
  printf("left=%d right=%d l=%d r=%d\n", left, right, l, r);
  for (int i = 0; i < 10; i++) printf("%d  ", a[i]);
  printf("\n");
  QuickSort(a, left, l - 1);
  QuickSort(a, l + 1, right);
}
int main() {
  int a[10] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
  QuickSort(a, 0, 9);
  for (int i = 0; i < 10; i++) {
    if (i == 0)
      printf("%d", a[i]);
    else
      printf(" %d", a[i]);
  }
  printf("\n");
  return 0;
}
