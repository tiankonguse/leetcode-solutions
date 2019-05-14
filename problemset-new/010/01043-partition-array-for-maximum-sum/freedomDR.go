package main

import "fmt"

func maxSumAfterPartitioning(A []int, K int) int {
	dp := make([]int, len(A)+1)
	for i := 0; i < len(A); i++ {
		maxx := 0
		for k := 1; k <= K && i-k+1 >= 0; k++ {
			if maxx < A[i-k+1] {
				maxx = A[i-k+1]
			}
			if dp[i+1] < dp[i+1-k]+maxx*k {
				dp[i+1] = dp[i+1-k] + maxx*k
			}
		}
	}
	return dp[len(A)]
}
func main() {
	fmt.Println("vim-go")
}
