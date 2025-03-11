#include <bits/stdc++.h>
using namespace std;
const int N = 100000;
int isprime[N + 1];
int p[N];
int ct = 0;
int main() {
  memset(isprime, 1, sizeof(isprime));
  for (int i = 2; i <= N; i++) {
    if (isprime[i]) {  // 为啥这一步是正确的？
      p[ct++] = i;
    }

    for (int j = 0; j < ct && i * p[j] <= N; j++) {
      isprime[i * p[j]] = 0;
      if (i % p[j] == 0) {
        break;  // 为何这一步是正确的？
      }
    }
  }
  for (int i = 0; i < ct; i++) {
    printf("%d\n", p[i]);
  }
  return 0;
}
