package main

import "fmt"

func search(nums []int, target int) int {
	lo, hi := 0, len(nums)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] < target {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	if lo == len(nums) || nums[lo] != target {
		return -1
	} else {
		return lo
	}
}
func main() {
	fmt.Println("vim-go")
}
