#include <bits/stdc++.h>

// 埃氏筛求 N 范围内的所有质数
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
const int N = 1000000;
const int M = 78499;
bool is[N];
int prm[M];
int prmCnt = 0;
int InitPrimes() {
  // O(n log log n)
  if (prmCnt > 0) return prmCnt;
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int j = i * i; j < N; j += i * 2) {
        is[j] = 0;
      }
    }
  }
  for (; i < N; i += 2) {
    if (is[i]) {
      prm[k++] = i;
    }
  }
  return prmCnt = k;
}

// 利用素数表，判断 n 是否为质数
// 时间复杂度 O(pi(sqrt(n)))，pi(x) 为不超过 x 的质数个数，大概复杂度为 O(sqrt(n)/log(sqrt(n)))
bool IsPrime(long long n) {
  if (n < N) {
    return !is[n];
  }
  for (int i = 0; i < prmCnt; i++) {
    long long p = prm[i];
    if (p * p > n) {
      break;
    }
    if (n % p == 0) {
      return false;
    }
  }
  return true;
}

// 判断一个数是否为质数
// 时间复杂度 O(sqrt(n))
bool IsPrime2(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return n >= 2;  // 1 不是质数, 2和3是质数
}

// 质因数分解
// 复杂度： O(sqrt(n))
std::vector<std::pair<int, int>> PrimeFactorization(int n) {
  std::vector<std::pair<int, int>> factors;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      int count = 0;
      while (n % i == 0) {
        n /= i;
        count++;
      }
      factors.emplace_back(i, count);
    }
  }
  if (n > 1) {
    factors.emplace_back(n, 1);
  }
  return factors;
}

// 计算 n 的所有约数
// 复杂度： O(sqrt(n))
std::vector<int> GetAllDivisors(int n) {
  std::vector<int> divisors;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      divisors.push_back(i);
      if (i != n / i) {
        divisors.push_back(n / i);
      }
    }
  }
  std::sort(divisors.begin(), divisors.end());
  return divisors;
}