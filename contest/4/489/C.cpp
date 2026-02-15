
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
  vector<vector<int>> dp;  // dp[l][r] 表示 在 [0,l] 与 [r,n) 进行匹配，最多可以匹配的长度
  string S;
  int n;
  int Dfs(int l, int r) {  // (l,r) 已经确定是回文串，现在判断 S[l] 和 S[r]
    if (l < 0 || r >= n) return r - l - 1;
    if (dp[l][r] != -1) return dp[l][r];
    if (S[l] == S[r]) {
      dp[l][r] = Dfs(l - 1, r + 1);
    } else {
      dp[l][r] = r - l - 1;
    }
    return dp[l][r];
  }

 public:
  int almostPalindromic(string s_) {
    S.swap(s_);
    n = S.size();
    int ans = 2;
    dp.resize(n + 1, vector<int>(n + 1, -1));
    // 第一步：枚举回文长度为奇数的情况
    for (int i = 0; i < n; i++) {
      int l = i - 1, r = i + 1;
      while (l >= 0 && r < n) {
        ans = max(ans, Dfs(l - 1, r));  // 删除 l
        ans = max(ans, Dfs(l, r + 1));  // 删除 r
        if (S[l] != S[r]) {
          break;
        }
        l--, r++;
      }
      if (l >= 0 || r < n) {
        ans = max(ans, r - l);
      }
    }

    // 第二步：枚举回文长度为偶数的情况

    for (int i = 0; i < n; i++) {
      int l = i, r = i + 1;
      while (l >= 0 && r < n) {
        ans = max(ans, Dfs(l - 1, r));  // 删除 l
        ans = max(ans, Dfs(l, r + 1));  // 删除 r
        if (S[l] != S[r]) {
          break;
        }
        l--, r++;
      }
      if (l >= 0 || r < n) {
        ans = max(ans, r - l);
      }
    }

    return ans;
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