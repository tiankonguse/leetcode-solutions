#include <bits/stdc++.h>

// 枚举判断 sqrt(N) 内的所有数字
std::vector<int> CalFactor1(int N) {
  std::vector<int> ans;
  for (int i = 1; i * i <= N; i++) {
    if (N % i == 0) {
      int j = N / i;
      ans.push_back(i);
      if (i != j) {
        ans.push_back(j);
      }
    }
  }
  return ans;
}

extern const int N = 1000000;
extern const int M = 300000;
extern bool is[N];
extern int prm[M];
extern int getprm();

// 最坏情况下遍历 sqrt(N) 内的所有素数
// 小于 K 的素数个数为 K/log(K), 这里 K=sqrt(N)
// 综合复杂度 sqrt(N)/log(sqrt(N))
vector<pair<int, int>> CalPrimeFactor(int N) {
  vector<pair<int, int>> primeFactors;

  int k = getprm();
  for (int i = 0; i < k; i++) {
    int num = 0;
    while (N % prm[i] == 0) {
      num++;
      N /= prm[i];
    }
    if (num > 0) {
      primeFactors.push_back({prm[i], 1});
    }

    // 最后一个可能，特殊判断
    if (is[N]) {
      primeFactors.push_back({N, 1});
      break;
    }
  }
}

void Dfs(int pos, int sum, vector<pair<int, int>>& primeFactors,
         std::vector<int>& ans) {
  int n = primeFactors.size();
  if (pos == n) {
    ans.push_back(sum);
    return;
  }
  auto [primeFactor, num] = primeFactors[pos];
  int base = 1;
  for (int i = 0; i <= num; i++) {
    Dfs(pos + 1, sum * base, primeFactors, ans);
    base = base * primeFactor;
  }
};

// 计算出所有素因子和个数，排列组合求出所有因子
std::vector<int> CalFactorByPrime(int N) {
  std::vector<int> ans;
  auto primeFactors = CalPrimeFactor(N);
  Dfs(0, 1, primeFactors, ans);
  return ans;
}