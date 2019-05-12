class Solution:
    def maxSumAfterPartitioning(self, A: List[int], K: int) -> int:
        n = len(A)
        dp = [0] * (n + 1)
        
        for i in range(n):
            v_max = A[i]
            for j in range(i, max(i - K, -1), -1):
                v_max = max(v_max, A[j])
                dp[i + 1] = max(dp[j] + (i - j + 1) * v_max, dp[i + 1])
        return dp[n]        
