package main

import "fmt"
//有障碍？？？直接置0就ok了，是我变聪明了吗，这不会是人生的错觉吧
func uniquePathsWithObstacles(obstacleGrid [][]int) int {
    m, n := len(obstacleGrid), len(obstacleGrid[0])
    dp := make([]int, n+1)
    dp[1] = 1
    for i := 0; i < m; i++ {
        for j := 1; j <= n; j++ {
            dp[j] = dp[j] + dp[j-1]
            if obstacleGrid[i][j-1] == 1 {
                dp[j] = 0
            }
        }
    }
    return dp[n]
}
func main() {
	fmt.Println("vim-go")
}
