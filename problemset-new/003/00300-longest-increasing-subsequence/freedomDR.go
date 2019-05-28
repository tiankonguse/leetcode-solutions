package main

import "fmt"

func max(v1, v2 int) int {
	if v1 > v2 {
		return v1
	} else {
		return v2
	}
}

//dp
func lengthOfLIS(nums []int) int {
	dp := make([]int, len(nums))
	ans := 0
	for i := range nums {
		dp[i] = 1
		for j := 0; j < i; j++ {
			//fmt.Println(i, j)
			if nums[i] > nums[j] {
				dp[i] = max(dp[i], dp[j]+1)
			}
		}
		ans = max(ans, dp[i])
		//fmt.Println(dp)
	}
	return ans
}

//二分
func lengthOfLIS(nums []int) int {
	dp := make([]int, len(nums))
	ans := 0
	for _, v := range nums {
		lo, hi := 0, ans
		for lo < hi {
			mid := lo + (hi-lo)/2
			if dp[mid] < v {
				lo = mid + 1
			} else {
				hi = mid
			}
		}
		dp[lo] = v
		if lo == ans {
			ans++
		}
	}
	return ans
}

func main() {
	fmt.Println("vim-go")
}
