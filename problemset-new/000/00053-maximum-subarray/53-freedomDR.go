package main

import "fmt"

//dp
func max(v1, v2 int) int {
	if v1 > v2 {
		return v1
	} else {
		return v2
	}
}

func maxSubArray(nums []int) int {
	ans := nums[0]
	dp := nums[0]
	for i := 1; i < len(nums); i++ {
		dp = max(nums[i], dp+nums[i])
		ans = max(dp, ans)
	}
	return ans
}
func main() {
	fmt.Println("vim-go")
}
