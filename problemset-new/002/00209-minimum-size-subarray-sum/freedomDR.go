package main

import "fmt"

func min(v1, v2 int) int {
	if v1 > v2 {
		return v2
	} else {
		return v1
	}
}
func minSubArrayLen(s int, nums []int) int {
	ans := int(1e9)
	sums, pos := 0, 0
	for i, v := range nums {
		sums += v
		for sums >= s {
			ans = min(ans, i-pos+1)
			sums -= nums[pos]
			pos++
		}
	}
	if ans == int(1e9) {
		return 0
	} else {
		return ans
	}
}
func main() {
	fmt.Println("vim-go")
}
