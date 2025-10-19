
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
class Solution {
  string s;
  int m;
  vector<vector<ll>> dp;  // dp[i][flag]  flag 代表是否进位，后i个数字在 flag 下有多少种组合

  //   mask=3 代表两个都不是前缀0， 1 代表第一个不是前缀0， 2 代表第二个不是前缀0， 0 代表都是前缀0
  ll Dfs(int p, int flag) {
    if (dp[flag][p] != -1) return dp[flag][p];
    const int v = s[p] - '0';

    ll ans = 0;
    for (int i = 0; i <= 9; i++) {
      for (int j = 0; j <= 9; j++) {
        // 情况1： 下一位不进位
        if (i + j == v + flag * 10) {
          ans += Dfs(p + 1, 0);
        }
        // 情况2： 下一位进位
        if (i + j == v + flag * 10 - 1) {
          ans += Dfs(p + 1, 1);
        }
      }
    }
    dp[flag][p] = ans;
    return ans;
  }

 public:
  long long countNoZeroPairs(long long n) {
    s = to_string(n);
    m = s.size();
    dp.resize(2, vector<ll>(m + 2, -1));
    dp[0][m] = 1;
    dp[1][m] = 0;
    return Dfs(0, 0);
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