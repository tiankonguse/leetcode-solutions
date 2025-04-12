// 求 C(n,m) % MOD ,MOD=1e9+7 需要预处理，然后 O(1) 提供任意查询

// 1. 预处理阶乘和逆元
// 2. C(n,m) = n!/(m!*(n-m)!) = n!*inv[m] % MOD * inv[n-m] % MOD

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7; /*  */
const int N = 1e6 + 10;

int fact[N], inv[N];

// Function to calculate a^k % MOD using binary exponentiation
// Parameters:
//   a - the base
//   k - the exponent
int qmi(int a, int k) {
  int res = 1;
  while (k) {
    if (k & 1) res = (long long)res * a % MOD;
    a = (long long)a * a % MOD;
    k >>= 1;
  }
  return res;
}

// 组合数封装为函数 C(n,m)
int C(int n, int m) {
  if (m < 0 || m > n) return 0;
  return (long long)fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) fact[i] = (long long)fact[i - 1] * i % MOD;
  inv[N - 1] = qmi(fact[N - 1], MOD - 2);
  for (int i = N - 2; i >= 0; i--) inv[i] = (long long)inv[i + 1] * (i + 1) % MOD;

  // 输出 10 以内的组合数
  // 双层循环输出 10 以内的组合数，直接输出答案，所有 n 一行，m 一列
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j <= i; j++) {
      cout << C(i, j) << " ";
    }
    cout << endl;
  }

  return 0;
}
