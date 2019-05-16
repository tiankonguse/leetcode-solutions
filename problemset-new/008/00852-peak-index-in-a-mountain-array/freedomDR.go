package main

import "fmt"

func peakIndexInMountainArray(A []int) int {
	lo, hi := 0, len(A)
	for lo < hi {
		mid := lo + (hi-lo)/2
		if A[mid] < A[mid+1] {
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
