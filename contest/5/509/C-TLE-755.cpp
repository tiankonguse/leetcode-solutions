
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
const int MOD = 1e9 + 7;
// 埃氏筛求 N 范围内的所有质数
/*
1e4 3.732020845644619
1e5 4.053948940531981
1e6 4.316983346365776
1e7 4.539375767702223
*/
const int N = 1000010;
const int M = 80000;
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
class Solution {
 public:
  int divisibleGame(vector<int>& nums) {
    InitPrimes();
    ll maxSum = -1, minK = 2;
    for (int i = 0; i < prmCnt; i++) {
      const int k = prm[i];
      ll sum = 0;
      for (const ll v : nums) {
        if (v % k == 0) {
          sum += v;
        } else {
          sum -= v;
          sum = max(sum, 0LL);
        }
        if (sum > maxSum) {
          maxSum = sum;
          minK = k;
        } else if (sum == maxSum) {
          minK = min(minK, (ll)k);
        }
      }
    }
    if (maxSum == 0) {
      maxSum = -1;
      minK = 2;
    }
    return (maxSum * minK % MOD + MOD) % MOD;
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