#include <bits/stdc++.h>

using namespace std;
const int N = 1000001;
typedef long long ll;
ll f[N];  // 动态规划:f[i]表示前i行完全铺满的方案总数

int main() {
  int n;
  scanf("%d", &n);
  // 边界条件
  f[0] = 1;
  f[1] = 1;
  f[2] = 2;

  // 递推
  for (int i = 3; i <= n; i++) {
    f[i] = (f[i - 1] + f[i - 2] + 2 * f[i - 3]) % 10000;
  }
  printf("%lld\n", f[n]);

  return 0;
}