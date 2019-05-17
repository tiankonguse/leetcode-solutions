package main

import "fmt"

// 这种题有没有什么规律啊，只能构造各种情况吗
func findMin(nums []int) int {
	lo, hi := 0, len(nums)
	ans := int(1e9)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if nums[mid] > nums[lo] {
			ans = int(math.Min(float64(nums[lo]), float64(ans)))
			lo = mid + 1
		} else if nums[mid] == nums[lo] {
			ans = int(math.Min(float64(nums[lo]), float64(ans)))
			ans = int(math.Min(float64(findMin(nums[lo:mid])), float64(ans)))
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
