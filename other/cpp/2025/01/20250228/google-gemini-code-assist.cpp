// query C(n,m) % MOD ,MOD=1e9+7, n=1e5

#include <iostream>
#include <vector>

using namespace std;

long long power(long long base, long long exp, long long mod) {
  long long res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) res = (res * base) % mod;
    base = (base * base) % mod;
    exp /= 2;
  }
  return res;
}

long long modInverse(long long n, long long mod) { return power(n, mod - 2, mod); }

long long combinations(int n, int m, long long mod, vector<long long>& fact, vector<long long>& invFact) {
  if (m < 0 || m > n) return 0;
  return (((fact[n] * invFact[m]) % mod) * invFact[n - m]) % mod;
}

int main() {
  // n=1e+5, m=1e+5
  long long mod = 1e9 + 7;

  // n 需要改成常量 N
  const int N = 1e5 + 10;
  vector<long long> fact(N + 1);
  vector<long long> invFact(N + 1);
  fact[0] = 1;
  invFact[0] = 1;
  for (int i = 1; i < N; i++) {
    fact[i] = (fact[i - 1] * i) % mod;
    invFact[i] = modInverse(fact[i], mod);
  }

  // 输出 10 以内的组合数
  // 双层循环输出 10 以内的组合数，直接输出答案，所有 n 一行，m 一列
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j <= i; j++) {
      cout << combinations(i, j, mod, fact, invFact) << " ";
    }
    cout << endl;
  }


  return 0;
}
