
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
  vector<vector<vector<ll>>> dp;  // dp[i][flag]  flag 代表是否进位，后i个数字在 flag 下有多少种组合

  bool Check(int i, int j, int mask) {
    int iMask = mask & 1;
    int jMask = (mask >> 1) & 1;
    if (iMask == 1 && i == 0) return false;
    if (jMask == 1 && j == 0) return false;
    return true;
  }
  //   mask=3 代表两个都不是前缀0， 1 代表第一个不是前缀0， 2 代表第二个不是前缀0， 0 代表都是前缀0
  ll Dfs(int p, int flag, int mask) {
    if (p == m) {
      if (flag == 0 && mask == 3) {
        return 1;
      } else {
        return 0;
      }
    }
    if (dp[flag][p][mask] != -1) return dp[flag][p][mask];
    ll ans = 0;
    const int v = s[p] - '0';

    for (int i = 0; i <= 9; i++) {
      for (int j = 0; j <= 9; j++) {
        int newMask = mask;
        if (i != 0) newMask |= 1;
        if (j != 0) newMask |= 2;
        // 情况1： 下一位不进位
        if (i + j == v + flag * 10 && Check(i, j, mask)) {
          ans += Dfs(p + 1, 0, newMask);
        }
        // 情况2： 下一位进位
        if (i + j == v + flag * 10 - 1 && Check(i, j, mask)) {
          ans += Dfs(p + 1, 1, newMask);
        }
      }
    }
    dp[flag][p][mask] = ans;
    return ans;
  }

 public:
  long long countNoZeroPairs(long long n) {
    s = to_string(n);
    m = s.size();
    dp.resize(2, vector<vector<ll>>(m + 1, vector<ll>(4, -1)));
    return Dfs(0, 0, 0);
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