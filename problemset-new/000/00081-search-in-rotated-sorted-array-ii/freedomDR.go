package main

import "fmt"

//这道题很烦
func search(nums []int, target int) bool {
	lo, hi := 0, len(nums)
	res := false
	for lo < hi && !res {
		mid := lo + (hi-lo)/2
		if nums[mid] == target {
			return true
		} else if nums[mid] > nums[lo] {
			res = res || search(nums[mid+1:hi], target)
			hi = mid
		} else {
			if lo != len(nums) {
				res = res || search(nums[lo:mid], target)
			}
			lo = mid + 1
		}
	}
	//fmt.Println(lo, nums)
	if res || (lo != len(nums) && nums[lo] == target) {
		return true
	} else {
		return false
	}
}
func main() {
	fmt.Println("vim-go")
}
