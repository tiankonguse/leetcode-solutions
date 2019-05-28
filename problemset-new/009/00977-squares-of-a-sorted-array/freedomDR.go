package main

import "fmt"

func sortedSquares(A []int) []int {
	lo, hi := 0, len(A)
	ans := make([]int, len(A))
	for lo < hi {
		mid := lo + (hi-lo)/2
		if A[mid] < 0 {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	p := 0
	lo--
	for lo >= 0 && hi < len(A) {
		lv := A[lo] * A[lo]
		rv := A[hi] * A[hi]
		if lv > rv {
			ans[p] = rv
			hi++
			p++
		} else {
			ans[p] = lv
			lo--
			p++
		}
	}
	for lo >= 0 {
		ans[p] = A[lo] * A[lo]
		lo--
		p++
	}
	for hi < len(A) {
		//fmt.Println(hi)
		ans[p] = A[hi] * A[hi]
		hi++
		p++
	}
	return ans
}
func main() {
	fmt.Println("vim-go")
}
