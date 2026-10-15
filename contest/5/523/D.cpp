
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
const int N = 10000;
const int M = 2000;
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
  int N;
  // dp[s][i] 从第 i 个素数起，素数和不超过 s 的最大和，此时的最少质数，以及选择的第一个下标=
  vector<vector<tuple<int, int, int>>> dp;
  tuple<int, int, int> Dfs(const int s, const int p) {
    if (p >= prmCnt || prm[p] > N || s < prm[p]) return {0, 0, 0};
    auto& [sum, cnt, index] = dp[s][p];
    if (sum != -1) {
      return dp[s][p];
    }
    sum = 0;
    cnt = 0;
    // 选择
    const auto [sum1, cnt1, index1] = Dfs(s - prm[p], p + 1);
    // 不选择
    const auto [sum0, cnt0, index0] = Dfs(s, p + 1);

    const tuple<int, int, int> ans1 = {sum1 + prm[p], cnt1 + 1, p};
    const tuple<int, int, int> ans0 = {sum0, cnt0, index0};

    if (sum1 + prm[p] > sum0) {
      return dp[s][p] = ans1;
    } else if (sum1 + prm[p] < sum0) {
      return dp[s][p] = ans0;
    } else {  // sum 相等，优先比较 cnt
      if (cnt1 + 1 < cnt0) {
        return dp[s][p] = ans1;
      } else if (cnt1 + 1 > cnt0) {
        return dp[s][p] = ans0;
      } else {  // sum 相等, cnt 相等，比较index，当前是选择，显然最小
        return dp[s][p] = ans1;
      }
    }
  }

 public:
  vector<int> maxPrimeSubset(int n, int s) {
    N = n;
    // 1000 以内最多 168个素数
    dp.resize(s + 1, vector<tuple<int, int, int>>(200, {-1, -1, -1}));
    InitPrimes();
    auto [ansSum, ansCnt, ansIndex] = Dfs(s, 0);
    // MyPrintf("prmCnt=%d ansSum=%d\n", prmCnt, ansSum);
    vector<int> ans;
    ans.reserve(ansCnt);
    int sum = ansSum, index = ansIndex;
    while (sum > 0) {
      ans.push_back(prm[index]);
      auto [ansSum, ansCnt, ansIndex] = Dfs(sum - prm[index], index + 1);
      sum = ansSum, index = ansIndex;
    }
    return ans;
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(int n, int s, const vector<int>& ans) {
  TEST_SMP2(Solution, maxPrimeSubset, ans, n, s);  //
}

int main() {
  int n = 1000;
  int s = 1000;
  vector<int> ans;
  Test(n, s, ans);
  return 0;
}

#endif