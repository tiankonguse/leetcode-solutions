#include <bits/stdc++.h>
using namespace std;
double a[105];
int main() {
  double b, maxa, mina, sum;
  int k = 1, i = 0;
  char c = '0';
  while (~scanf("%lf", &b)) {
    a[i++] = b;
  }
  // cout<<"i="<<i<<endl;
  maxa = a[0];
  mina = a[0];
  sum = a[0];
  for (int j = 1; j <= i; j++) {
    if (a[j] > maxa) {
      maxa = a[j];
    }
    if (a[j] < mina) {
      mina = a[j];
    }
    sum = sum + a[j];
  }
  for (int j = i; j >= 0; j--) {
    if (k == 1) {
      k = 0;
    } else {
      printf(" ");
    }
    printf("%.2lf", a[j]);
  }
  printf("\n%.2lf\n%.2lf\n%.2lf\n", maxa, mina, sum);
  return 0;
}
