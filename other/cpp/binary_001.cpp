#include <bits/stdc++.h>
using namespace std;
int BinarySearch(int a[], int key, int L, int R) {
  printf("L=%d R=%d\n", L, R);
  int mid;
  if (L > R) return -1;
  mid = (L + R) / 2;
  printf("mid=%d\n", mid);
  if (a[mid] == key) {
    return mid;
  } else if (a[mid] > key)
    return BinarySearch(a, key, L, mid - 1);
  else
    return BinarySearch(a, key, mid + 1, R);
}

int main() {
  int a[9] = {1, 3, 4, 5, 8, 16, 24, 55, 78};
  int key = 1;
  int pos = BinarySearch(a, key, 0, 8);
  if (pos == -1)
    printf("n");
  else
    printf("%d %d\n", key, pos);
  return 0;
}
