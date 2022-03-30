class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return nums[0] if n else 0
        dp = [[0] * (n + 2) for _ in range(2)]
        for i in range(2):
            for j in range(i, n - 1 + i):
                dp[i][j + 2] = max(dp[i][j + 1], nums[j] + dp[i][j])
        return max(itertools.chain.from_iterable(dp))