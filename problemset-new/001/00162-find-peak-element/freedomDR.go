package main

import "fmt"

//左闭右闭区间也好，尤其适合判断升降序列，也不会越界，要考虑剩两个元素时并且相等时，应该让区间变小，所以自然而然得加一个等号缩小区间
func findPeakElement(nums []int) int {
	lo, hi := 0, len(nums)-1
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] <= nums[mid+1] {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	return lo
}
func main() {
	fmt.Println("vim-go")
}
