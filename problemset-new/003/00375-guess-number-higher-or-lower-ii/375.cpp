
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

#define MyDebug(...) fprintf(stderr, __VA_ARGS__);

typedef long long ll;
int dp[222][222];
class Solution {
  int Dfs(int l, int r) {
    if (l > r) return 0;

    int& ret = dp[l][r];
    if (ret != -1) return ret;
    if (l == r) return 0;

    ret = INT_MAX;
    for (int i = l; i <= r; i++) {
      ret = min(ret, i + max(Dfs(l, i - 1), Dfs(i + 1, r)));
    }
    return ret;
  }

 public:
  int getMoneyAmount(int n) {
    memset(dp, -1, sizeof(dp));
    return Dfs(1, n);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const int& n, const int& ans) {  //
  TEST_SMP1(Solution, getMoneyAmount, ans, n);
}

int main() {
  Test(10, 16);
  Test(1, 0);
  Test(2, 1);
  return 0;
}

#endif