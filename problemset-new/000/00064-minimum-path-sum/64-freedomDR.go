package main

import "fmt"
//62,63,64连着呀，仅仅是初始条件不一样而已。。。。
func min(v1, v2 int) int {
    if v1 > v2 {
        return v2
    } else {
        return v1
    }
}


func minPathSum(grid [][]int) int {
    row, col := len(grid), len(grid[0])
    dp := make([]int, col+1)
    for i := 0; i <= col; i++ {
        dp[i] = int(1e9)
    }
    dp[1] = 0
    for i := 0; i < row; i++ {
        for j := 1; j <= col; j++ {
            dp[j] = min(dp[j-1], dp[j]) + grid[i][j-1]
        }
        //fmt.Println(dp)
    }
    return dp[col]
}
func main() {
	fmt.Println("vim-go")
}
