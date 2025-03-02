// 求 C(n,m) % MOD ,MOD=1e9+7, N=1e5, 需要预处理，然后 O(1) 提供任意查询

int main() {
  int n = 10;
  int m = 3;
  int MOD = 1e9 + 7;
  int N = 1e5;
  vector<vector<int>> dp(N + 1, vector<int>(N + 1));
  for (int i = 0; i <= N; ++i) {
    dp[i][0] = 1;
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
    }
  }
  cout << dp[n][m];
  return 0;
}