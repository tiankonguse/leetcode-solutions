package main

import "fmt"

//经典DP
func uniquePaths(m int, n int) int {
	dp := make([]int, n+1)
	for i := 0; i < m; i++ {
		dp[1] = 1
		for j := 1; j <= n; j++ {
			dp[j] = dp[j] + dp[j-1]
		}
	}
	return dp[n]
}
func main() {
	fmt.Println("vim-go")
}
