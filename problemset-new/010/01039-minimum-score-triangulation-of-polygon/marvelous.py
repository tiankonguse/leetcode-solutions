class Solution:
    def minScoreTriangulation(self, A: List[int]) -> int:
        n = len(A)
        dp = [[0] * n for _ in range(n)]
        for j in range(3, n + 1):
            for i in range(0, n - j + 1):
                for k in range(i + 1, i + j - 1):
                    curr = dp[i][k] + A[i] * A[k] * A[i + j - 1] + dp[k][i + j - 1]
                    if not dp[i][i + j - 1]:
                        dp[i][i + j - 1] = curr
                    else:
                        dp[i][i + j - 1] = min(curr, dp[i][i + j - 1])
        return dp[0][n - 1]        
