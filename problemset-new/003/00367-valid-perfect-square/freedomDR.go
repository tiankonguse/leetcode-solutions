package main

import "fmt"

func isPerfectSquare(num int) bool {
	lo, hi := 1, num/2
	for lo < hi {
		mid := lo + (hi-lo)/2
		if mid*mid < num {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	if lo*lo == num {
		return true
	} else {
		return false
	}
}

func main() {
	fmt.Println("vim-go")
}
