
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

const double pi = acos(-1.0), eps = 1e-7;
const int inf = 0x3f3f3f3f, ninf = 0xc0c0c0c0, mod = 1000000007;
const int max3 = 2010, max4 = 20010, max5 = 200010, max6 = 2000010;

class Solution {
  vector<vector<ll>> nums;
  vector<vector<ll>> dp;
  vector<ll> flag;
  vector<ll> zero;
  const vector<ll>& Dfs(int n) {
    if (n == 0) {
      return zero;
    }
    auto& dp0 = dp[n];
    if (flag[n]) return dp0;
    flag[n] = 1;

    auto& dp1 = Dfs(n - 1);
    for (int i = 0; i < n; i++) {
      dp0[i] = (dp0[i] + dp1[i]) % mod;
      dp0[i + 1] = (dp0[i + 1] + dp1[i]) % mod;
    }
    // printf("n=%d\n", n);
    // for (int i = 0; i <= n; i++) {
    //   printf("%d->%lld\n", i, dp0[i]);
    // }
    return dp0;
  }

 public:
  int countKReducibleNumbers(const string& s, int k) {
    int n = s.length();
    nums.resize(k + 1, vector<ll>(n + 1, 0));

    zero.resize(n + 1, 0);
    zero[0] = 1;

    flag.resize(n + 1, 0);
    dp.resize(n + 1, vector<ll>(n + 1, 0));

    // 第一次手动模拟， n 的值可以降低到 800
    int preOne = 0;
    for (int j = 0; j < n; j++) {
      int nn = n - j;  // 包含 i 剩余的二进制长度
      if (s[j] == '1') {
        // 值为0时
        const auto& dp0 = Dfs(nn - 1);
        // printf("preOne=%d n-1=%d dp[1]=%lld\n", preOne, n - 1, dp0[1]);
        for (int i = 0; i < nn; i++) {
          nums[0][i + preOne] = (nums[0][i + preOne] + dp0[i]) % mod;
        }
        preOne++;
      } else {
        // do nothing
      }
    }

    if (k == 1) {
      return nums[0][1];
    }

    for (int i = 1; i < k; i++) {
      // 对 [0,nn]的数字进行模拟
      for (int j = 1; j <= n; j++) {
        int c = __builtin_popcount(j);
        nums[i][c] = (nums[i][c] + nums[i - 1][j]) % mod;
      }
    }
    return nums[k - 1][1];
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const string& s, int k, const int& ans) {
  TEST_SMP2(Solution, countKReducibleNumbers, ans, s, k);
}

int main() {
  Test("1000", 1, 3);
  Test("111", 1, 3);
  Test("1000", 2, 6);
  Test("1", 3, 0);
  return 0;
}

#endif