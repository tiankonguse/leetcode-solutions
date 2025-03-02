
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
/*
You are given a string s and an integer k.
In one operation, you can replace the character at any position with the next or previous letter in the alphabet
(wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and
replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and
replacing 'z' with the previous letter results in 'y'. Return the length of the longest palindromic subsequence of s
that can be obtained after performing at most k operations. A subsequence is a non-empty string that can be derived from
another string by deleting some or no characters without changing the order of the remaining characters. A palindrome is
a string that reads the same forward and backward.

Constraints:

1 <= s.length <= 200
1 <= k <= 200
s consists of only lowercase English letters.
*/
int dp[202][202][202];
class Solution {
  int n;
  string s;

 public:
  int longestPalindromicSubsequence(string& s_, int k) {
    s.swap(s_);
    n = s.size();
    memset(dp, -1, sizeof(dp));
    return dfs(0, n - 1, k);
  }

  int dfs(int left, int right, int k) {
    if (left > right) {
      return 0;
    }
    int& ret = dp[left][right][k];
    if (ret != -1) {
      return ret;
    }
    ret = 0;

    // 情况1: left 与 right 相等
    if (left == right) {
      return ret = 1;
    }

    // 情况2: left 与 right 进行匹配，最多修改 k 次
    int match = Trans(s[left], s[right]);
    if (match <= k) {
      ret = max(ret, 2 + dfs(left + 1, right - 1, k - match));
    }
    // 情况3: left 与 right 不进行匹配, 不修改
    ret = max(ret, dfs(left + 1, right, k));
    ret = max(ret, dfs(left, right - 1, k));
    return ret;
  }
  int Trans(char a, char b) {
    int diff = abs(a - b);
    return min(diff, 26 - diff);
  }
};

#ifdef USACO_LOCAL_JUDGE

void Test(const vector<int>& jump, const int& ans) {
  // TEST_SMP1(Solution, minJump, ans, jump);
}

int main() {
  Test({1, 2, 3}, 3);
  return 0;
}

#endif