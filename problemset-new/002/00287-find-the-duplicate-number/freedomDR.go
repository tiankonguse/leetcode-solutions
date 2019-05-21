package main

import "fmt"

func findDuplicate(nums []int) int {
	slow, fast := 0, 0
	for {
		slow = nums[slow]
		fast = nums[nums[fast]]
		if slow == fast {
			fast = 0
			for nums[slow] != nums[fast] {
				fast = nums[fast]
				slow = nums[slow]
			}
			return nums[slow]
		}
	}
}
func findDuplicate(nums []int) int {
	lo, hi := 1, len(nums)
	for lo < hi {
		mid := lo + (hi-lo)/2
		cnt := 0
		for i := 0; i < len(nums); i++ {
			if nums[i] <= mid {
				cnt++
			}
		}
		if cnt <= mid {
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
