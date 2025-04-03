// 使用区间动态规划递归形式求最长回文串

#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  // dp[i][j] 表示 s[i..j] 的是否是回文串，是的话返回长度，不是的话返回负无穷
  vector<vector<pair<int, int>>> dp;
  int longestPalindromeSubStr(const string& s) {
    int n = s.size();
    dp.resize(n, vector<pair<int, int>>(n, pair<int, int>(0, 0)));
    int ans = 1;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        ans = max(ans, dfs(s, i, j));
      }
    }
    return ans;
  }

 private:
  const int kNoAns = -2;
  pair<int, int> dfs(const string &s, int i, int j) {
    if (i > j) return {1, 0};
    if (i == j) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == s[j]) {
      int ans = dfs(s, i + 1, j - 1);
      if (ans == kNoAns) {  // 子问题没答案，当前问题也没答案
        dp[i][j] = kNoAns;
      } else {
        dp[i][j] = 2 + ans;
      }
    } else {
      dp[i][j] = kNoAns;  // 没有答案，标记为负无穷
    }
    return dp[i][j];
  }
};
int main() {
  Solution s;
  cout << s.longestPalindromeSubStr("bbbbab") << endl;
  return 0;
}
