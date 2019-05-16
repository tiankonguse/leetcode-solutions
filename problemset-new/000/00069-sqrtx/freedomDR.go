package main

import "fmt"

func mySqrt(x int) int {
	lo, hi := 0, x
	for lo < hi {
		mid := lo + (hi-lo)/2
		if mid*mid < x {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	if lo*lo == x {
		return lo
	} else {
		return lo - 1
	}
}

func main() {
	fmt.Println("vim-go")
}
