#include <bits/stdc++.h>
using namespace std;
const int N = 1000;
int isprime[N + 1];  // 标记该数是否为素数，1表示是，0表示不是
int p[N];            // 存储素数
int ct = 0;          // 素数的个数
int main() {
  memset(isprime, 1, sizeof(isprime));  // 初始化
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) {  // 如果i没有被筛掉，就是素数
      p[ct++] = i;
    }
    for (int j = 0; j < ct && i * p[j] <= N; j++) {  // 素数的倍数
      isprime[i * p[j]] = 0;                         // 不是素数
      if (i % p[j] == 0) {                           // 保证p[j]是最小素数因子
        break;
      }
    }
  }
  for (int i = 0; i < ct; i++) {
    printf("i=%d %d\n", i, p[i]);
  }
  return 0;
}