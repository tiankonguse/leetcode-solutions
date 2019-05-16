package main

import "fmt"

func twoSum(numbers []int, target int) []int {
	for i := 0; i < len(numbers)-1; i++ {
		lo, hi, t := i+1, len(numbers), target-numbers[i]
		for lo < hi {
			mid := lo + (hi-lo)/2
			if numbers[mid] < t {
				lo = mid + 1
			} else {
				hi = mid
			}
		}
		if lo != len(numbers) && numbers[lo] == t {
			return []int{i + 1, lo + 1}
		}
	}
	return []int{}
}
func main() {
	fmt.Println("vim-go")
}
