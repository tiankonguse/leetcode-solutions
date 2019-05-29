package main

import "fmt"

//记忆花搜索
func get(dp []int, n int) int {
	if dp[n] != 0 {
		return dp[n]
	}
	dp[n] = get(dp, n-1) + get(dp, n-2)
	return dp[n]
}

func climbStairs(n int) int {
	dp := make([]int, n+1)
	dp[0] = 1
	dp[1] = 1
	return get(dp[:], n)
}
func main() {
	fmt.Println("vim-go")
}
