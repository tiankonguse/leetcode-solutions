// 质因数分解
#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  int m = (int)(sqrt(n) + 1);
  for (int i = 2; i <= m; i++) {
    if (n % i == 0) {
      while (n % i == 0) {  // 对于每一个质因数不断去除，保证不会有合数因子的出现
        printf("%d ", i);
        n /= i;
      }
    }
  }
  return 0;
}