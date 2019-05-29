package main

import "fmt"

func min(v1, v2 int) int {
	if v1 < v2 {
		return v1
	} else {
		return v2
	}
}

func minCostClimbingStairs(cost []int) int {
	if len(cost) == 0 {
		return 0
	}
	if len(cost) == 1 {
		return cost[0]
	}
	dp := make([]int, len(cost))
	dp[0] = cost[0]
	dp[1] = cost[1]
	for i := 2; i < len(cost); i++ {
		dp[i] = min(dp[i-1]+cost[i], cost[i]+dp[i-2])
	}
	return min(dp[len(cost)-1], dp[len(cost)-2])
}
func main() {
	fmt.Println("vim-go")
}
