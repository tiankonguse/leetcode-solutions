#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  int flag = 0;  // 统计个数
  int m = (int)(sqrt(n) + 1);
  for (int i = 2; i <= m; i++) {
    if (n % i == 0) {
      while (n % i == 0) {  // 对于每一个质因数不断去除，保证不会有合数因子的出现
        flag++;
        printf("%d ", i);
        n /= i;
      }
    }
  }
  if (n != 1) {
    flag++;  // 防止输入的n本身就是一个素数
    if (flag == 1)
      printf("%d\n", n);
    else
      printf("*%d\n", n);
  }

  return 0;
}