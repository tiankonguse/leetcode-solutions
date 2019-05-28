package main

import "fmt"

func superEggDrop(K int, N int) int {
	dp := make([]int, K+1)
	m := 0
	for dp[K] < N {
		m += 1
		for k := K; k > 0; k-- {
			dp[k] = dp[k-1] + dp[k] + 1
		}
	}
	return m
}
func main() {
	fmt.Println("vim-go")
}
