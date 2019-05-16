package main

import "fmt"

func arrangeCoins(n int) int {
	lo, hi := 0, int(1<<16)
	for lo < hi {
		mid := lo + (hi-lo)/2
		t := mid * ((mid + 1) / 2)
		if mid%2 == 0 {
			t += mid / 2
		}
		if t < n {
			lo = mid + 1
		} else {
			hi = mid
		}
	}
	t := lo * ((lo + 1) / 2)
	if lo%2 == 0 {
		t += lo / 2
	}
	if t == n {
		return lo
	} else {
		return lo - 1
	}
}
func main() {
	fmt.Println("vim-go")
}
