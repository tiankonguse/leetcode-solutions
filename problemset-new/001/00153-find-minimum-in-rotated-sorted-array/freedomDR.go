package main

import "fmt"

// 二分查找
func findMin(nums []int) int {
	lo, hi := 0, len(nums)
	ans := int(1e9)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] > nums[lo] {
			ans = int(math.Min(float64(nums[lo]), float64(ans)))
			lo = mid + 1
		} else {
			hi = mid
			ans = int(math.Min(float64(nums[mid]), float64(ans)))
		}
	}
	return ans
}

func main() {
	fmt.Println("vim-go")
}
