
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
vector<int> primes;
int isInit = 0;
void Init() {
  if (isInit) return;
  isInit = 1;
  InitPrimes();
  ll sum = 0;
  primes.reserve(M);
  for (int i = 0; i < prmCnt; i++) {
    sum += prm[i];
    if (sum >= N) break;
    if (is[sum]) {
      primes.push_back(sum);
    }
  }
}
class Solution {
 public:
  int largestPrime(int n) {
    Init();
    auto it = upper_bound(primes.begin(), primes.end(), n);
    if (it == primes.begin()) {
      return 0;
    }
    return *(--it);
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