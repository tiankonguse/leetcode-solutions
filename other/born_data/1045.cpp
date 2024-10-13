#include <bits/stdc++.h>
using namespace std;
// 1 0.00002 0.0000000002
// 1 0.000002 0.000000000002
// 1 0.00002 -0.0000000002
// 1 0.000002 -0.000000000002
/*
1 0 1
x1=0.00000+1.00000i;x2=0.00000-1.00000i

3 0 0
X1=x2=0.00000

1 0 8
x1=0.00000+2.82843i;x2=0.00000-2.82843i
*/

const double eps = 1e-5;
const long long X = 1e5;
int main() {
  double a, b, c, delta, x1, x2;
  scanf("%lf%lf%lf", &a, &b, &c);
  delta = b * b - 4 * a * c;
  if (delta < 0) {
    double p = -b / (2 * a);
    double q = sqrt(4 * a * c - b * b) / (2 * a);
    if (a < 0) {
      q = -q;
    }
    long long P = p * X;
    long long Q = q * X;
    // printf("p=%.7f q=%.7f Q=%lld eps=%.6f\n", p, q, Q);
    if (Q == 0) {
      printf("x1=x2=%.5f\n", P * 1.0 / X);
    } else {
      printf("x1=%.5f+%.5fi;", P * 1.0 / X, q);
      printf("x2=%.5f-%.5fi\n", P * 1.0 / X, q);
    }
  } else {
    x1 = (-b + sqrt(delta)) / (2 * a);
    x2 = (-b - sqrt(delta)) / (2 * a);
    long long X1 = x1 * X;
    long long X2 = x2 * X;
    // printf("%lld %lld X=%lld eps=%.6f\n", X1, X2, X, eps);
    if (X1 == X2) {
      printf("x1=x2=%.5f\n", X1 * 1.0 / X);
    } else {
      if (X1 < X2) {
        swap(X1, X2);
        swap(x1, x2);
      }
      printf("x1=%.5f;x2=%.5f\n", X1 * 1.0 / X, X2 * 1.0 / X);
    }
  }
  return 0;
}
