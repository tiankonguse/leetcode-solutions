// 使用区间动态规划递归形式求最长回文串

#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  // dp[i][j] 表示 s[i..j] 的最长回文子序列长度
  vector<vector<int>> dp;
  int longestPalindromeSubseq(string s) {
    int n = s.size();
    dp.resize(n, vector<int>(n, -1));
    return dfs(s, 0, n - 1);
  }

 private:
  const int NINF = -1e9;
  int dfs(const string &s, int i, int j) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == s[j]) {
      dp[i][j] = 2 + dfs(s, i + 1, j - 1);
    } else {
      dp[i][j] = max(dfs(s, i + 1, j), dfs(s, i, j - 1));
    }
    return dp[i][j];
  }
};
int main() {
  Solution s;
  cout << s.longestPalindromeSubseq("bbbbab") << endl;
  return 0;
}
