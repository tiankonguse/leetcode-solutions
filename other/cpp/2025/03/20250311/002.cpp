#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int a[N];
int n, k;
int part(int a[], int left, int right) {
  int r = left + rand() % (right - left + 1);  // 随机找一个数作为基准
  swap(a[left], a[r]);
  int i = left + 1;
  int j = right;
  while (i < j) {
    while (i < j && a[j] >= a[left]) j--;
    while (i < j && a[i] <= a[left]) i++;
    swap(a[i], a[j]);
  }
  swap(a[left], a[i]);
  return i;
}
void quickselect(int a[], int left, int right) {
  int p = part(a, left, right);  // 找到基准
  if (k < p)
    quickselect(a, left, p - 1);
  else if (k > p)
    quickselect(a, p + 1, right);
  else {
    printf("%d", a[k]);
    exit(0);
  }
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  quickselect(a, 0, n - 1);
  // printf("%d\n",a[k]);
  return 0;
}