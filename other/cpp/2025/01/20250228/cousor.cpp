// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, MOD = 1e9 + 7;

int qpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = (long long)res * a % MOD;
    a = (long long)a * a % MOD;
    b >>= 1;
  }
  return res;
}

int C(int n, int m) {
  if (m > n) return 0;
  int res = 1;
  for (int i = 1; i <= m; i++) {
    res = (long long)res * (n - i + 1) % MOD;
    res = (long long)res * qpow(i, MOD - 2) % MOD;
  }
  return res;
}

int main() {
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