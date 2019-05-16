package main

import "fmt"

// 快速幂
func myPow(x float64, n int) float64 {
	res := 1.0
	base := x
	neg := false
	if n < 0 {
		n = -n
		neg = true
	}
	for n != 0 {
		if n%2 == 1 {
			res *= base
		}
		n /= 2
		base *= base
	}
	if neg {
		return 1.0 / res
	} else {
		return res
	}
}
func main() {
	fmt.Println("vim-go")
}
