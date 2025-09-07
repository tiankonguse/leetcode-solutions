
#ifdef USACO_LOCAL_JUDGE
#include <bits/stdc++.h>

#include "base.h"
using namespace std;
#endif

int debug = 1;
#define MyPrintf(...)               \
  do {                              \
    if (debug) printf(__VA_ARGS__); \
  } while (0)

typedef long long ll;
const int N = 1000000;
const int M = 78499;
bool is[N];
int prm[M];
int K = 0;
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
int getprm() {
  if (K != 0) return K;
  // O(n log log n)
  int e = (int)(sqrt(0.0 + N) + 1), k = 0, i;
  memset(is, 1, sizeof(is));
  prm[k++] = 2;
  is[0] = is[1] = 0;
  for (i = 4; i < N; i += 2) is[i] = 0;
  for (i = 3; i < e; i += 2) {
    if (is[i]) {
      prm[k++] = i;
      for (int s = i + i, j = i * i; j < N; j += s) is[j] = 0;
    }
  }
  for (; i < N; i += 2)
    if (is[i]) prm[k++] = i;
  return K = k;
}

class Solution {
  vector<pair<int, int>> factors;
  int m;  // 不同因子的个数
  int k;
  void Init(int n, int k) {
    this->k = k;
    for (int i = 0; i < K && n > 1; i++) {
      int p = prm[i];
      int cnt = 0;
      while (n % p == 0) {
        n /= p;
        cnt++;
      }
      if (cnt > 0) {
        factors.emplace_back(p, cnt);
      }
      // 剪枝
      if (n > 0 && is[n]) {
        factors.emplace_back(n, 1);
        n = 1;
        break;
      }
    }
    m = factors.size();
  }

  vector<int> vals;
  vector<int> ansNums;
  int ans;
  void CheckAns() {
    int minVal = *min_element(vals.begin(), vals.end());
    int maxVal = *max_element(vals.begin(), vals.end());
    if (maxVal - minVal < ans) {
      ans = maxVal - minVal;
      ansNums = vals;
    }
  }
  int MyPow(int a, int b) {
    int res = 1;
    while (b--) res *= a;
    return res;
  }
  // 第 mi 个因子，使用了 use 个，分给到第 ki 个数
  void Dfs(int mi, int ki, int use) {
    if (mi == m) {
      CheckAns();
      return;
    }
    auto [p, cnt] = factors[mi];
    int leftNum = cnt - use;  // 第 mi 个因子还剩下多少个
    if (leftNum == 0) {
      Dfs(mi + 1, 0, 0);
      return;
    }
    if (ki + 1 == k) {  // 只剩最后一个选择了
      vals[ki] *= MyPow(p, leftNum);
      Dfs(mi + 1, 0, 0);
      vals[ki] /= MyPow(p, leftNum);
      return;
    }
    int base = 1;
    for (int i = 0; i <= leftNum; i++) {
      vals[ki] *= base;
      Dfs(mi, ki + 1, use + i);
      vals[ki] /= base;
      base *= p;
    }
  }

 public:
  vector<int> minDifference(int n, int k) {
    getprm();
    Init(n, k);
    vals.resize(k, 1);  // 初始值都是 1
    ans = n - 1;        // 最大差值
    ansNums.resize(k, 1);
    ansNums.back() = n;
    Dfs(0, 0, 0);
    return ansNums;
  }
};

#ifdef USACO_LOCAL_JUDGE

// void Test(const vector<int>& jump, const int& ans) {
//   // TEST_SMP1(Solution, minJump, ans, jump);
// }

int main() {
  // Test({1, 2, 3}, 6);
  return 0;
}

#endif