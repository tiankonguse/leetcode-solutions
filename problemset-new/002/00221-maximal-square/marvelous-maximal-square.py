class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        if not matrix:
            return 0
        rows, cols = len(matrix), len(matrix[0])
        dp = [[0] * cols for _ in range(rows)]
        ov = [0] * cols
        oh = [0] * cols

        for i in range(cols):
            dp[0][i] = 1 if matrix[0][i] == '1' else 0
            ov[i] = 1 if matrix[0][i] == '1' else 0

        for i in range(rows):
            dp[i][0] = 1 if matrix[i][0] == '1' else 0

        for i in range(1, rows):
            oh[0] = 1 if matrix[i][0] == '1' else 0
            for j in range(1, cols):
                oh[j] = 1 + oh[j - 1] if matrix[i][j] == '1' else 0
                ov[j] = 1 + ov[j] if matrix[i][j] == '1' else 0

                if not matrix[i][j] == '1':
                    continue
                dp[i][j] = 1

                if matrix[i - 1][j - 1] == '1' and matrix[i - 1][j] == '1' and matrix[i][j - 1] == '1':
                    dp[i][j] = min(oh[j], ov[j], dp[i - 1][j - 1] + 1)

        return max(itertools.chain.from_iterable(dp)) ** 2
